#!/usr/bin/python
# -*- coding:utf-8 -*-

import os, sys
import logging, time, re, ConfigParser
import common, deploy
import cluster

'''
Description:
 To deploy k8s binary 
 file indent = space(4)
'''

if __name__=='__main__':

    logging.basicConfig(level=logging.DEBUG,
                    format='[%(asctime)s][%(levelname)s] %(message)s')
    try:
        ini_file, cmd, host = common.read_opt()
        #config = common.config_map(ini_file, "kube")
        #upgrade_versions = common.config_map(ini_file, "upgrade")
    except:
        common.print_usage()
    # get cluster names
    config = ConfigParser.ConfigParser()
    config.read(ini_file)
    clusternms = config.sections()
    clusternms.remove('upgrade')   
 
    # 아래의 내용은 cluster 객체로 전환
    # 위에서 받은 clusternm로 반복하여 객체 생성 가능 지금은 테스트로 하나만 생성
    # 2016-06-13 클러스터 루프 돌면서 작업 하도록 변경
    # upgrade, deploy 같은 순차로 해야 하는것은 그ㄹ대로 두고
    # backup, install등은 스레드를 만들어 동시에 실행하도록 변경
    clusters = []
    for c in range(0,len(clusternms)): 
        clusters.append(cluster.Cluster())
        clusters[c].load_conf(ini_file, clusternms[c])
        print('%s cluster object %s' %(clusternms[c], clusters[c].clusternm))
    #master = []
    #master.append(config['master'])
    #nodes = config['nodes'].split(",")
    #etcds = config['etcds'].split(",")
    #confpath = config['confpath']
    #backuppath = config['backuppath']
    #acc = config['acc']
    #passwd = config['password']
    #etcddatapath = config['etcddatapath']
    #etcdbackuppath = config['etcdbackuppath']
    #apiserver = config['apiserver']
    #remotepath = config['remotebinpath'] 
    #sourcepath = upgrade_versions['sourcebinpath']
    #orgpath = upgrade_versions['originbinpath']
    #kube_ex_version = upgrade_versions['kube_ex_version']
    #kube_version = upgrade_versions['kube_version']
    #docker_ex_version = upgrade_versions['docker_ex_version']
    #cker_version = str(upgrade_versions['docker_version'])
    #ckersrcpath = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'src',
    #                             'docker-engine_' + docker_version + '-0-trusty_amd64.deb')
   
    role = {}

    for i in clusters[0].nodes : 
        role[i] = "minion"
    for i in clusters[0].master:
        role[i] = "master"

    if host is None:
        allnodes = clusters[0].nodes + clusters[0].master
    else:
        allnodes = [host]

    #for n in nodes + master: 
    for n in allnodes:
        node_role = role.get(n)

        if cmd == 'export' :
            try:
                clusters[0].export_kube_conf(n)
                #deploy.export_kube_conf(n, confpath, backuppath, acc, passwd)
            except Exception, e:
                logging.error('export kubernetes config is fail : %s - %s' % (n, e))

            # etcd snapshot backup, last node
            if allnodes.index(n) + 1 == len(allnodes):
                for e in clusters[0].etcds:
                    backupcmd = 'ssh ' + clusters[0].acc + '@' + e + ' sudo /opt/bin/etcdctl \
backup --data-dir ' + clusters[0].etcddatapath + ' --backup-dir \
' + clusters[0].etcdbackuppath + '.' + time.strftime("%Y%m%d%H%m", time.localtime())
                    clusters[0].connect_using_pexpect(e, backupcmd)

        elif cmd == 'deploy' :
            # kubernetes service down
            res = False
            while res == False:
                deploy.cmd_service(n, 'stop', 'flanneld', acc, passwd)
                time.sleep(2) 
                deploy.deploy_kube_bin(n, sourcepath, remotepath, node_role, acc, passwd)
                time.sleep(3) 
                deploy.cmd_service(n, 'start', 'flanneld', acc, passwd)
                res = deploy.check_service(n, 'ps -ef | grep /opt/bin/kube | grep -v grep | wc -l',
                                          acc, passwd)

        elif cmd == 'rollback' : 
            # kubernetes binary rollback
            res = deploy.diff_kube_version(n, apiserver, kube_ex_version, node_role)

            if res == True:
                logging.info('%s kube binary version is old enough %s' %(n, kube_ex_version))
            else:
                logging.info('%s node - rollback' %(n))
                deploy.cmd_service(n, 'stop', 'flanneld', acc, passwd)
                time.sleep(2) 
                deploy.deploy_kube_bin(n, orgpath, remotepath, node_role, acc, passwd)
                time.sleep(3) 
                deploy.cmd_service(n, 'start', 'flanneld', acc, passwd)
                deploy.check_service(n, 'ps -ef | grep /opt/bin/kube | grep -v grep | wc -l',
                                     acc, passwd)

        elif cmd == 'docker':
            # docker upgrade/downgrade
            if node_role == 'master':
                res = True
            else:
                res, checkversion = deploy.diff_docker_version(n, docker_ex_version, 
                                                              docker_version, acc, passwd)
      
            #res = False; checkversion = "1.8.3"
            if res == True :
                logging.info('%s node - the docker version is what you need' %
                             n)
            else:
                # false
                logging.info('%s node - need to install docker version : %s -> %s' % 
                             (n, checkversion, docker_version)) 
                if int(kube_version.split(".")[1]) == 2:
                    # drain the target using kubectl
                    # after that be changed using kubectl proxy api
                    node_ip = deploy.get_node_ip(n)
                    draincmd = '/opt/bin/kubectl -s http://' + apiserver + ' drain ' + node_ip + ' --force'
                    res = False
                    while res == False:
                        res,out = deploy.connect_using_pexpect(n, draincmd, acc, passwd)
                        if res is True:
                            #logging.info('%s node - now drain %s' % (n, out))
                            logging.info('%s node - now drain' % (n ))
                        else: 
                            logging.error('%s drains fail, You better check the machine status' % n)
                else:
                    # no drain function
                    res = True
                    while res == True:
                        deploy.cmd_service(n, 'stop', 'flanneld', acc, passwd)
                        time.sleep(2)
                        res = deploy.check_service(n, 'ps -ef | grep /opt/bin/kube | grep -v grep | wc -l',
                                                   acc, passwd)
                        if res == True:
                            logging.warn('%s node - kubelet proc is now running' % n)
                        else:
                            logging.info('%s node - kubelet proc is stop' % n)
                
                deploy.install_docker(n, docker_version, dockersrcpath, acc)
                time.sleep(2)
                version_flag, version = deploy.diff_docker_version(n, docker_ex_version, 
                                                              docker_version, acc, passwd)
                #print('docker - %s' %version)
                if version_flag == True:
                    logging.info('%s node - the docker version is what you need' % n)
                else:
                    logging.error('%s node - docker installation is failed' % n)

                if int(kube_version.split(".")[1]) == 2:
                    # drain the target using kubectl
                    # after that be changed using kubectl proxy api
                    node_ip = deploy.get_node_ip(n)
                    draincmd = '/opt/bin/kubectl -s http://' + apiserver + ' uncordon ' + node_ip
                    res = False
                    while res == False:
                        res,out = deploy.connect_using_pexpect(n, draincmd, acc, passwd)
                        if res is True:
                            logging.info('%s node - now normal status' % n)
                        else:
                            logging.error('%s uncordon fail, You better check the machine status' % n)
                else:
                    # no drain function
                    res = True
                    while res == True:
                        deploy.cmd_service(n, 'start', 'flanneld', acc, passwd)
                        time.sleep(2)
                        res = deploy.check_service(n, 'ps -ef | grep /opt/bin/kube | grep -v grep | wc -l',
                                                   acc, passwd)
                        if res == True:
                            logging.info('%s node - kubelet proc is now running' % n)
                        else:
                            logging.error('%s node - kubelet proc cannot start' % n)
                    
            
        else:
            logging.warn('%s is not cmd' % (cmd))
            common.print_usage()
            sys.exit(1)
        time.sleep(3)
