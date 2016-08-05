#!/usr/bin/python
# -*- coding: utf-8 -*-
import os, sys
import logging, pexpect, time, re, simplejson
'''
Description:
  k8s node object
  file indent = space(4)
'''
logging.basicConfig(level=logging.INFO,
     format='[%(asctime)s][%(levelname)s] %(message)s')

class Node(object):

    _role = None
    _nodehost = None
    _nodeip = None
    _platform = None
    _binary = []
    _confpath = None
    _binpath = None
    _os = None
    _acc = None
    _password = None
    _versions = {}
    #_version_dict = {}

    def __init__(self, clusterinfo, host, role, config):
        self._clusterid = clusterinfo[0]
        self._clusternm = clusterinfo[1]
        self._role = role
        self._nodehost = host
        self._platform = config['platform']
        self._confpath = config['confpath']
        self._binpath = config['binpath']
        self._acc = config['acc']
        self._passwd = config['password']
        self._backuppath = config['backuppath']
        self._etcdbackuppath = config['etcdbackuppath']
        self._etcddatapath = config['etcddatapath']
        logging.info("host %s - role %s " %(host, role))
        self.set_node_ip()
        self.display()

    def display(self):
        print('[%s][%s]-----------------' %(self._nodehost, self._role))
        print('  acc      : %s' %(self._acc))
        print('  pin      : %s' %(self._passwd))
        print('  platform : %s' %(self._platform))
        print('  confpath : %s' %(self._confpath))

    def get_nodehost(self):
        return self._nodehost
    def get_noderole(self):
        return self._role
    def get_node_ip(self):
        return self._nodeip

    def connect_using_pexpect(self, target, cmd):
        # make connection do something on remote host
        msg = 'Are you sure you want to continue connecting'
        child = pexpect.spawn('/bin/bash', ['-c', cmd])
        index = child.expect([msg, 'password:', pexpect.EOF, pexpect.TIMEOUT])

        if index == 0 :
            child.sendline('yes')
            index = child.expect([msg, 'password:', pexpect.EOF, pexpect.TIMEOUT])

        if index == 1:
            logging.debug('%s server is require passwd to login ' % (target))
            logging.debug('node: %s cmd: %s' % (target, cmd))
            child.sendline(self._passwd)
            child.expect(pexpect.EOF)
            res = True
        elif index == 2:
            logging.debug('%s server is NOT require passwd to login ' % (target))
            logging.debug('node: %s cmd: %s' % (target, cmd))
            child.after
            res = True
        else:
            logging.error('connot connect to %s' % target)
            res = False
        return res, child.before.strip('\n')

    def export_config(self):
        msg = 'Are you sure you want to continue connecting'
        target = self._nodehost
        backuppath = self._backuppath
        dirfullpath = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                   backuppath, target)

        if os.path.isdir(dirfullpath) is False:
            os.makedirs(dirfullpath)

        if self._role == 'etcd':
            child = pexpect.spawn('scp -r ' + self._acc + '@' +
                              target + ':' + self._confpath + '/etcd*' + ' ' +
                              dirfullpath + '/')
        else:
            child = pexpect.spawn('scp -r ' + self._acc + '@' +
                              target + ':' + self._confpath + '/kube*' + ' ' +
                              self._acc + '@' +
                              target + ':' + self._confpath + '/flanneld*' + ' ' +
                              dirfullpath + '/')
        
        index = child.expect([msg, 'password:', pexpect.EOF, pexpect.TIMEOUT])

        if index == 0 :
            child.sendline('yes')
            index = child.expect([msg, 'password:', pexpect.EOF, pexpect.TIMEOUT])

        if index == 1:
            child.sendline(self._passwd)
            child.expect(pexpect.EOF)
            return True
        elif index == 2:
            logging.info('%s kubeconfs are now exporting' %(target))
            child.after
            return True
        else:
            logging.error('cannot connect to %s' % target)
            return False

    def backup_etcd(self):
        # backup etcd
        cmd = 'ssh ' + self._acc + '@' + self._nodehost + ' sudo /opt/bin/etcdctl \
backup --data-dir ' + self._etcddatapath + ' --backup-dir \
' + self._etcdbackuppath + '.' + time.strftime("%Y%m%d%H%M", time.localtime())
        try:
            self.connect_using_pexpect(self._nodehost, cmd)
            logging.info('%s etcd are now exporting data-dir(%s)' %(self._nodehost, self._etcddatapath))
            return True
        except Exception as e:
            logging.error('%s exception is occur - %s' %(self.backup_etcd.__name__, e))
            return False, e

    def deploy_binary(self, sourcepath):
        # deploy new binary
        sourcefullpath = os.path.join(sourcepath, self._role)

        cmd = 'scp -r ' + sourcefullpath + '/' + ' ' + self._acc + '@' + self._nodehost + ':/tmp/'
        copycmd = 'ssh ' + self._acc +'@'+ self._nodehost + ' sudo cp /tmp/'+ self._role  + '/kube* \
' + self._binpath + '/'
        logging.info("%s" %(cmd))
    def deploy_binary_real(self, sourcepath):
        # deploy new binary
        msg = 'Are you sure you want to continue connecting'
        sourcefullpath = os.path.join(sourcepath, self._role)

        cmd = 'scp -r ' + sourcefullpath + '/' + ' ' + self._acc + '@' + self._nodehost + ':/tmp/'
        res, out = self.connect_using_pexpect(self._nodehost, cmd)
        copycmd = 'ssh ' + self._acc +'@'+ self._nodehost + ' sudo cp /tmp/'+ self._role  + '/kube* \
' + self._binpath + '/'
        cres, cout = self.connect_using_pexpect(target, copycmd)
        self.check_bin_version()
        return cres

    def set_node_ip(self):
        # search node ip in /etc/hosts
        f = open('/etc/hosts' , 'r')
        lines = f.readlines()
        ip_list = []
        for line in lines:
            if re.search(self._nodehost, line):
                ip_list.append(line.split()[0])
        sorted_ip_list = sorted(set(ip_list))
        for i in sorted_ip_list:
            if re.search('^#', i):
                sorted_ip_list.remove(i) 

        if len(sorted_ip_list) == 1:
            self._nodeip = sorted_ip_list[0]
        else:
            logging.error("%s node ip is duplicated %s" %(self._nodehost, sorted_ip_list))

    def check_bin_version(self, comp):
        if comp == 'docker':
            cmd = 'ssh ' + self._acc + '@' + self._nodehost + ' docker --version'
        else:
            cmd = 'ssh ' + self._acc + '@' + self._nodehost + ' ' + os.path.join(self._binpath, comp) + ' --version'

        res, output = self.connect_using_pexpect(self._nodehost, cmd)
        #print(output)
        if comp == 'etcd':
            for i in output.split('\n'):
                if re.search('etcd Version', i):
                    version = i.split()[2]
        elif comp == 'flanneld':
            version = output.strip('\r')
        elif comp == 'docker':
            version = output.split()[2].strip(',')
        else:
            #kube*
            version = output.split()[1].strip('v')      
        #print(comp, version)
        return version
        
    def set_node_version(self):
        # check current binary version(kube, etcd, flanneld)
        # _version_dict = {'kubelet':'1.2.4', 'kube-proxy':'1.2.4', 'binary':'version',...}
        _version_dict = {}
        #print('node %s - role %s  - %s' %(self._nodehost, self._role, _version_dict))
        if self._role == 'master':
            binary = ['kube-apiserver', 'kube-controller-manager', 'kube-scheduler', 'flanneld']
        elif self._role == 'node':
            binary = ['kubelet', 'kube-proxy', 'flanneld', 'docker']
        else:
            # etcd
            binary = ['etcd']
        #print(self._nodehost, self._role, binary)
        
        for b in binary:
            _version_dict[b] = self.check_bin_version(b)
            #print(self._role, b)
        self._versions = _version_dict
        #print(_version_dict)

    def get_cur_version(self):
        return self._versions

    def check_svc(self):
        # to verify kube service wherther node role
        cmd = 'ssh ' + self._acc + '@' + self._nodehost + ' ps -ef | grep /opt/bin/kube | grep -v grep | wc -l'
        res, out = self.connect_using_pexpect(self._nodehost, cmd)

        if int(out) >= 2:
            logging.info('%s server, kubernetes is now running - proc : %s' % (self._nodehost, out))
            return True
        else:
            logging.error('%s server, kubernetes is NOT working - proc : %s' % (self._nodehost, out))
            return False

    def control_svc(self, cmd, svc):
        logging.info('%s - %s - %s' %(self.control_svc.__name__, cmd, svc))
#        runcmd = 'ssh ' + self._acc + '@' + target + ' ' + '\" sudo service ' + svcnm + ' ' + action + ' \"'
#        i = 0
#        res = False
#        while res == False:
#            res, out = self.connect_using_pexpect(target, runcmd)
#            i += 1
#            if i > 3 and res == False:
#                logging.error('%s - %s service cannot %s ' %(target, svcnm, action))
#                sys.exit(2)

    def install_bin(self):
        pass
    def check_nodeinfo(self):
        pass

