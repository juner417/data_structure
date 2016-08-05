#!/usr/bin/python 
#-*- coding: utf-8-*-

import os, sys, time
import pexpect, logging, re, urllib2, simplejson
import common

''' 
Description:
  k8s cluster object
  file indent = space(4)
'''
logging.basicConfig(level=logging.INFO,
     format='[%(asctime)s][%(levelname)s] %(message)s')

class Cluster(object):
    _clusternm = None
    _platform = None
    _master = []
    _nodes = []
    _etcds = []
    _confpath = None
    _acc = None
    _passwd = None
    _apiserver = None
    _kube_check_version = {}
    _deploy = None
    _backuppath = None
    _flanneldbackend = None
    _etcdbackuppath = None
    _etcddatapath = None
    _remotebinpath = None
    _sourcepath = None
    _orgpath = None
    _kube_cur_version = None
    _kube_version = None
    _docker_cur_version = None
    _docker_version = None 

    def __init__(self, ini_file, clusternm):
        self.load_conf(ini_file, clusternm)

    @property
    def get_clusternm(self):
        return self._clusternm
    @property
    def get_nodes(self):
        return self._nodes
    @property
    def get_master(self):
        return self._master
    @property
    def get_apiserver(self):
        return self._apiserver
    @property
    def get_deploy(self):
        return self._deploy
    @property
    def get_kube_cur_version(self):
        return self._kube_cur_version
    @property
    def get_kube_next_version(self):
        return self._kube_version
    @property
    def get_docker_cur_version(self):
        return self._docker_cur_version
    @property
    def get_docker_next_version(self):
        return self._docker_version
    @property
    def get_kube_check_version(self):
        return self._kube_check_version
    @property
    def get_clusterplatform(self):
        return self._platform

    def load_conf(self, ini_file, clusternm):
        try: 
            config = common.config_map(ini_file, clusternm)
            upgrade_versions = common.config_map(ini_file, 'upgrade')
        except Exception as e:
            logging.error('[%s] exception is occur - %s' %(load_conf.__name__, e))
        
        self._master.append(config['master'])
        self._nodes = config['nodes'].split(",")
        self._etcds = config['etcds'].split(",")
        self._clusternm = clusternm
        self._platform = config['platform']
        self._confpath = config['confpath']
        self._acc = config['acc']
        self._passwd = config['password']
        self._apiserver = config['apiserver']
        self._deploy = config['deploy']
        self._backuppath = config['backuppath'] + '_' + self._clusternm
        self._flanneldbackend = config['flanneldbackend']
        self._etcdbackuppath = config['etcdbackuppath']
        self._etcddatapath = config['etcddatapath']
        self._remotebinpath = config['remotebinpath']
        self._sourcepath = upgrade_versions['sourcebinpath']
        self._orgpath = upgrade_versions['originbinpath']
        self._kube_cur_version = upgrade_versions['kube_cur_version']
        self._kube_version = upgrade_versions['kube_next_version']
        self._docker_cur_version = upgrade_versions['docker_cur_version']
        self._docker_version = str(upgrade_versions['docker_next_version'])
        self._exportsvc = config['exportsvc'].split(",")

    def display(self):
        print('------------------------------------')
        print('# %s cluster info                   ' % (self._clusternm))
        print('------------------------------------')
        print('master: %s, apiserver: %s' %(self._master, self._apiserver))
        print('nodes: %s, etcd: %s' %(self._nodes, self._etcds))
        print('acc: %s, passwd: %s' %(self._acc, self._passwd))
        print('backuppath: %s, etcdbackuppath: %s' %(
                                      self._backuppath, self._etcdbackuppath))
        print('remotebinpath: %s' %(self._remotebinpath))
        print('flannedbackend: %s' %(self._flanneldbackend))
        print('------------------------------------')

    def has_elements(self, target):
        
        res = self._master.count(target) + self._nodes.count(target) + self._etcds.count(target)
        if res == 0:
            logging.error('%s is Not in nodes(master, nodes, etcds)' %(target))
            #sys.exit(1)
            return False
        else:
            return True

    def export_kube_conf(self, target):
        msg = 'Are you sure you want to continue connecting'
        self.has_elements(target)
        
        dirfullpath = os.path.join(os.path.dirname(os.path.abspath(__file__)), 
                                   self._backuppath, target)

        if os.path.isdir(dirfullpath) is False:
            os.makedirs(dirfullpath)

        child = pexpect.spawn('scp -r ' + self._acc + '@' + 
                              target + ':' + self._confpath + '/kube*' + ' ' +
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

    def export_kube_svc(self):
        # export kubernetes svc, rc, deployments using kubectl
        dirfullpath = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                   self._backuppath)

        if os.path.isdir(dirfullpath) is False:
            os.makedirs(dirfullpath)
        svcs = self._exportsvc
        for svc in svcs:
            cmd = '/opt/bin/kubectl -s http://' + self._apiserver + ' get ' + svc + ' -o yaml --all-namespaces'
            filenm = self._clusternm + '_' + svc + '.yaml' 
            filepath = os.path.join(dirfullpath, filenm)

            try:
                res, yaml = self.connect_using_pexpect(self._deploy, cmd)
                f = open(filepath, 'w') 
                f.write(yaml)
                logging.info('%s export kubernetes %s using kubectl : %s' %(self._deploy, svc, filenm))
            except Exception as e:
                logging.error('[%s] exception is occur - %s' %(export_kube_svc.__name__, e))
            f.close()

    def backup_etcd(self):
        # backup etcd
        for e in self._etcds:
            cmd = 'ssh ' + self._acc + '@' + e + ' sudo /opt/bin/etcdctl \
backup --data-dir ' + self._etcddatapath + ' --backup-dir \
' + self._etcdbackuppath + '.' + time.strftime("%Y%m%d%H%M", time.localtime())
            try: 
                self.connect_using_pexpect(e, cmd) 
                logging.info('%s etcd are now exporting data-dir(%s)' %(e, self._etcddatapath))
            except Exception as e:
                logging.error('[%s] exception is occur - %s' %(backup_etcd.__name__, e)) 
 
    def export_all(self):
        # export kube svc, config, etcd
        for n in self._nodes + self._master:
            self.export_kube_conf(n)
        self.export_kube_svc()
        self.backup_etcd()

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

    def deploy_kube_bin(self, target, role, cmd):
        # deploy new binary
        msg = 'Are you sure you want to continue connecting'
        if cmd == 'kube_upgrade':
            sourcefullpath = os.path.join(self._sourcepath, role)
        else:
            sourcefullpath = os.path.join(self._orgpath, role)

        cmd = 'scp -r ' + sourcefullpath + '/' + ' ' + self._acc + '@' + target + ':/tmp/'
        res, out = self.connect_using_pexpect(target, cmd)
        copycmd = 'ssh ' + self._acc +'@'+ target + ' sudo cp /tmp/'+ role  + '/kube* \
' + self._remotebinpath + '/'
        cres, cout = self.connect_using_pexpect(target, copycmd)
        return cres

    def get_api(self, url):
        # get api result
        try:
            # using json
            res = simplejson.load(urllib2.urlopen(url))
        except urllib2.HTTPError as err:
            logging.error(err - url)
            sys.exit(2)
        except urllib2.URLError as err:
            logging.error(err - url)
            sys.exit(2)
        return res

    def get_kube_version(self, jsondict, role, comp):
        # get kube binary version
        verdict = {}
        if role == 'master':
            keys = jsondict.keys()
            for i in comp:
                verdict[i] = jsondict['gitVersion'].strip('v')
        elif role == 'minion':
            keys = jsondict['status']['nodeInfo'].keys()
            for i in comp:
                verdict[i] = jsondict['status']['nodeInfo'][i+'Version'].strip('v')
        return verdict


    def get_node_ip(self, target):
        # search node ip in /etc/hosts
        target_ip = None
        f = open('/etc/hosts' , 'r')
        lines = f.readlines()
        for line in lines:
            if re.search(target, line):
                target_ip = line.split()[0]
        return target_ip

    def check_kube_version(self, target, role, version):
        version_dict = {}
        ip_dict = {}
        res = None
        target_ip = None

        target_ip = self.get_node_ip(target)
        if target_ip is None:
            logging.error('Host : %s is not in /etc/hosts file. Plz check the hosts file' % target)
            sys.exit(2)

        if role == 'master':
            binary = ['kube-apiserver', 'kube-controller-manager', 'kube-scheduler']
            url = 'http://' + self._apiserver + '/version'
        else:
            binary = ['kubelet', 'kubeProxy']
            url = 'http://' + self._apiserver + '/api/v1/nodes/' + target_ip

        version_dict = self.get_kube_version(self.get_api(url), role, binary)
        self._kube_check_version = version_dict
        
        for i in version_dict.values():
            if i == version:
                res = True
            else:
                res = False
                return res
                break
        return res

    def get_docker_version(self, target):
        # get target docker version
        # 지금은 docker tcp가 localhost로 열려 있어서 docker 커맨드를 직접입력 후 확인
        # 나중에 변경 필요 api 호출로(get_api 사용)
        runcmd = 'ssh ' + self._acc + '@' + target + ' \"docker version | grep \"Version\" | \
                  sort | uniq | awk \'{print \$2}\'\"'
        res, version = self.connect_using_pexpect(target, runcmd)
        return version

    def check_docker_version(self, target, version):
        # compare between docker versions
        try:
            docker_version = self.get_docker_version(target).strip('\r')
        except:
            logging.error('Cannot get the docker version in %s' % (target))

        if docker_version == version:
            # normal status
            res = True
        else:
            # need to install a indicated version
            # docker_version is not same with confversion or weird
            res = False
        return res, docker_version

    def check_service(self, target, cmd):
        # check the kube services
        runcmd = 'ssh ' + self._acc + '@' + target + ' ' + cmd

        res, out = self.connect_using_pexpect(target, runcmd)
        if int(out) >= 2:
            logging.info('%s server, kubernetes is now running - proc : %s' % (target, out))
            return True
        else:
            logging.error('%s server, kubernetes is NOT working - proc : %s' % (target, out))
            return False

    def send_cmd_to_server(self, target, svcnm, action):
        # service start/stop
        runcmd = 'ssh ' + self._acc + '@' + target + ' ' + '\" sudo service ' + svcnm + ' ' + action + ' \"'
        i = 0
        res = False
        while res == False:
            res, out = self.connect_using_pexpect(target, runcmd)
            i += 1
            if i > 3 and res == False:
                logging.error('%s - %s service cannot %s ' %(target, svcnm, action))
                sys.exit(2)

    def install_docker(self, target, version):
        # to intall docker
        srclist = os.listdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'src'))
        for f in srclist:
            if re.search(version, f):
                dockersrcpath = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'src', f)
        copycmd = 'scp ' + dockersrcpath + ' ' + self._acc + '@' + target + ':/tmp/'
        instcmd = 'ssh ' + self._acc + '@' + target + ' \" sudo dpkg -i /tmp/\"' + os.path.split(dockersrcpath)[1]

        i = 0
        cres = False
        ires = False
        while cres == False:
            cres, cout = self.connect_using_pexpect(target, copycmd)
            if cres == True:
                child = pexpect.spawn('/bin/bash', ['-c', instcmd])
                child.expect('[default=N] ?')
                child.sendline('N')
                child.expect(pexpect.EOF)
                ires = self.get_docker_version(target)
                if ires == False:
                    cres = False
                    i += 1
                    if i > 3 :
                        logging.error('%s-v%s connot install docker' %(target, self._docker_version))
                        sys.exit(2)

    def do_upgrade(self):
        pass
    def do_rollback(self, target):
        pass
