#!/usr/bin/python
#-*- coding: utf-8 -*-

import os, sys
import logging, common, urllib2, simplejson, re, time
from node import Node
'''
Description:
  k8s cluster object
  file indent = space(4)
'''
logging.basicConfig(level=logging.INFO,
     format='[%(asctime)s][%(levelname)s] %(message)s')


class Cluster(object):

    _clusternm = None
    _clusterid = None
    _clusterinfo = []
    _clusterver = {}
    _apiserver = None
    #_kube_check_version = {}
    _cluster_nodelist = {}
    _deploym = None
    _deployed = None
    _installed = False
    _backuppath = None
    _cur_kube_versions = {}
    _cur_etcd_versions = {}
    _delaytime = None
    config = {}
    upgrade_versions = {}

    def __init__(self, ini_file, clusternm):
        # to loading config file 
        self.load_conf(ini_file, clusternm)
        # and create node object
        self.create_node()
        self.check_cluster_initiation():

    def get_init(self):
        return self._installed

    def get_clusternm(self):
        return self._clusternm

    def load_conf(self, ini_file, clusternm):
        try:
            self.config = common.config_map(ini_file, clusternm)
            self.upgrade_versions = common.config_map(ini_file, 'upgrade')
        except Exception as e:
            logging.error(' exception is occur - %s' %( e))

        self._clusternm = clusternm
        self._clusterinfo.append(self._clusterid)
        self._clusterinfo.append(self._clusternm)
        self._backuppath = self.config['backuppath'] 
        self._apiserver = self.config['apiserver']
        self._platform = self.config['platform']
        self._deploym = self.config['deploy']
        self._exportsvc = self.config['exportsvc'].split(",")
        self._acc = self.config['acc']
        self._password = self.config['password']
        self._sourcepath = self.upgrade_versions['sourcebinpath']
        self._delaytime = float(self.upgrade_versions['delay_time'])

    def create_node(self):
        # 수정필요 : 지금음 cluster객체가 node를 dictionary로 관리하지만
        # node객체를 tree형태로 관리하면 좀더 편할거 같음
        self._cluster_nodelist['master'] = []
        self._cluster_nodelist['node'] = []
        self._cluster_nodelist['etcd'] = []
        for m in self.config['master'].split(","):
            self._cluster_nodelist['master'].append(Node(self._clusterinfo, 
            m, 'master', self.config))
        for n in self.config['nodes'].split(","):
            self._cluster_nodelist['node'].append(Node(self._clusterinfo, 
            n, 'node', self.config))
        for e in self.config['etcds'].split(","):
            self._cluster_nodelist['etcd'].append(Node(self._clusterinfo, 
            e, 'etcd', self.config))
    
    def do_export_conf(self):
        for k in self._cluster_nodelist.keys():
            #print(k)
            for n in self._cluster_nodelist[k]:
                n.get_nodehost() 
                n.export_config()

    def do_backup_etcd(self):
        for e in self._cluster_nodelist['etcd']:
            e.backup_etcd()

    def do_export_svc(self):
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
                res, yaml = self.connect_using_pexpect(self._deploym, cmd)
                f = open(filepath, 'w')
                f.write(yaml)
                logging.info('%s export kubernetes %s using kubectl : %s' %(
                             self._deploym, svc, filenm))
                f.close()
            except Exception as e:
                logging.error(' exception is occur - %s' %( e))

    def connect_using_pexpect(target, cmd):
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
            child.sendline(self._password)
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

    def get_api(self, url):
        # get api result
        try:
            # using json
            err = False
            res = simplejson.load(urllib2.urlopen(url))
        except urllib2.HTTPError as err:
            logging.error('%s - %s' %(err, url))
            sys.exit(2)
        except urllib2.URLError as err:
            logging.error('%s - %s' %(err, url))
            sys.exit(2)
        return res, err

    def get_node_ip(self, target):
        # search node ip in /etc/hosts
        target_ip = None
        f = open('/etc/hosts' , 'r')
        lines = f.readlines()
        for line in lines:
            if re.search(target, line):
                target_ip = line.split()[0]
        return target_ip

    def deploy_node(self, role=None):
        # deploy node
        if role == None:
            roles = "all"
        else:
            roles = self._cluster_nodelist.keys()

        for k in roles:
            for n in self._cluster_nodelist[k]:
                n.deploy_binary(self._sourcepath)
    
    def check_cluster_initiation(self):
        url = 'http://' + self._apiserver + '/version'
        res, err = self.get_api(url)

        if err == False: 
            flag = True
        else: 
            flag = False
        self._installed = flag

        
    def do_install(self):
        # initial installation
        if self._installed = True:
            logging.info('%s cluster was installed' %(self._clusternm))
            return False
            sys.exit(1)
        else:
            logging.info('%s cluster is now intalling' %(self._clusternm))

        for k in self._cluster_nodelist.keys():
            for n in self._cluster_nodelist[k]:
                # deploy host file
                # deploy kube, flanneld, etcd service script and init.d config
                # kube binary deploy(master, node, flanneld)
                # etcd binary deploy
                # 


    def set_cur_version(self):
        # check current binary version(kube, etcd, flanneld)
        # using node's.set_node_version
        # 이 부분은 수정이 필요함 왜냐하면 굳이 node객체가 가지고 있는 버전정로를 
        # 클러스터 객체가 또 가지고 있을 필요는 없음 
        for k in self._cluster_nodelist.keys():#node, master, etcd

            tmp_arr_role_hosts = []
            for n in self._cluster_nodelist[k]:# hdtest1
                tmp_dict_host_versions = {}
                nodehost = n.get_nodehost()
                noderole = n.get_noderole()
                n.set_node_version()
                # n.get_cur_version() return a set of nodes binary version 
                # {'nodehost':{'binary':'version',...}}
                tmp_dict_host_versions[nodehost] = n.get_cur_version()
                tmp_arr_role_hosts.append(tmp_dict_host_versions)
            # self._cur_kube_versions = {'master':[{'host':{'apiserver':'123', 'scheduler':'123', ...}}], 
            #                            'node':[{'host':{'apiserver':'123', 'scheduler':'123', ...}}, {} ...]}
            self._cur_kube_versions[k] = tmp_arr_role_hosts 

    def do_upgrade_cluster(self):
        self.set_cur_version()

        for k in self._cluster_nodelist.keys():
            for n in self._cluster_nodelist[k]:
                res = False
                nodehost = n.get_nodehost()
                noderole = n.get_noderole()
                next_versions = {}
                #print(nodehost, noderole)
                if noderole == 'master':
                    #vdict_keys = ['kube-apiserver', 'kube-controller-manager', 'kube-scheduler', 'flanneld']
                    vdict_keys = ['kube-apiserver', 'kube-controller-manager', 'kube-scheduler']
                elif noderole == 'node':
                    #vdict_keys = ['kubelet', 'kube-proxy', 'flanneld', 'docker']
                    vdict_keys = ['kubelet', 'kube-proxy']
                else:
                    # etcd
                    vdict_keys = ['etcd']
                # self._cur_kube_versions = {master:[{host:{kube-apiserver:1.2.4, kube-scheduler:1.2.4}}], 
                #  node:[{host1:{kubelet:1.2.4,kubeproxy:1.2.4}}, {host2:{kubelet:1.2.4,kubeproxy:1.2.4}}, ...], 
                #  etcd:[{host1:{}, host2:{}} }
                # 주어진 role의 index를 알아내기 위한 루프
                for vdk in vdict_keys:
                    if re.search('kube*', vdk):
                        next_versions[vdk] = self.upgrade_versions['kube_next_version']
                    elif re.search('flanneld', vdk):
                        next_versions[vdk] = self.upgrade_versions['flanneld_next_version']
                    elif re.search('docker', vdk):
                        next_versions[vdk] = self.upgrade_versions['docker_next_version']
                    else:# etcd
                        next_versions[vdk] = self.upgrade_versions['etcd_next_version']

                self._next_versions = next_versions
                for i in range(0, len(self._cur_kube_versions[k])):
                    for vk in (self._cur_kube_versions[k])[i].keys():
                        if vk == nodehost: # k role의 여러 host version dict 
                            idx = i
                        else:
                            continue
                #self._cur_kube_versios[k][idx] 버전 확인을 위한 node의 version dict
                upgrade_flag = 0
                for vdk in vdict_keys:
                    # 모든 바이너리의 버전 확인
                    if (self._cur_kube_versions[k])[idx][nodehost][vdk] == self._next_versions[vdk]:
                        # 업그레이드 하려는 버전과 지금 버전이 동일
                        continue
                    else:
                        # 버전 다름
                        upgrade_flag = 1

                if upgrade_flag == 0:
                    logging.warn('current(%s) == next(%s) %s node already latest ' %(
                    self._cur_kube_versions[k][idx][nodehost][vdk], 
                    self._next_versions[vdk], nodehost)) 
                    continue
                else:
                    logging.info('current(%s) -> next(%s) %s node change versions ' %(
                    self._cur_kube_versions[k][idx][nodehost][vdk],
                    self._next_versions[vdk], nodehost))
                    while res == False:
                        n.control_svc('stop', 'flanneld')
                        time.sleep(self._delaytime)
                        n.deploy_binary(self._sourcepath)
                        time.sleep(self._delaytime)
                        n.control_svc('start', 'flanneld')
                        res = n.check_svc()

        #self.set_cur_version()
        #ver_res = self.check_kube_version()
        return True        

    def do_upgrade_docker(self):
        pass
    def do_rollback(self):
        pass
    def check_exist_cluster(self):
        pass

