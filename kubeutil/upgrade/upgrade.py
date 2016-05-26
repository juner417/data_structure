#!/usr/bin/python
# -*- coding:utf-8 -*-

import os, sys
import logging, time, re
import common, deploy

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
        config = common.config_map(ini_file, "kube")
        upgrade_versions = common.config_map(ini_file, "upgrade")
    except:
        common.print_usage()

    master = []
    master.append(config['master'])
    nodes = config['nodes'].split(",")
    etcds = config['etcds'].split(",")
    confpath = config['confpath']
    backuppath = config['backuppath']
    acc = config['acc']
    passwd = config['password']
    sourcepath = config['sourcebinpath']
    remotepath = config['remotebinpath'] 
    orgpath = config['originbinpath']
    etcddatapath = config['etcddatapath']
    etcdbackuppath = config['etcdbackuppath']
    apiserver = config['apiserver']
    kube_ex_version = upgrade_versions['kube_ex_version']
    kube_version = upgrade_versions['kube_version']
    docker_ex_version = upgrade_versions['docker_ex_version']
    docker_version = str(upgrade_versions['docker_version'])
    dockersrcpath = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'src',
                                 'docker-engine_' + docker_version + '-0-trusty_amd64.deb')
    
    role = {}

    for i in nodes : 
        #role[i] = "nodes"
        role[i] = "minion"
    for i in master:
        role[i] = "master"
    if host is None:
        allnodes = nodes + master
    else:
        allnodes = [host]

    #for n in nodes + master: 
    for n in allnodes:
        node_role = role.get(n)

        if cmd == 'export' :
            try:
                deploy.export_kube_conf(n, confpath, backuppath, acc, passwd)
            except:
                logging.error('export kubernetes config is fail')

            # etcd snapshot backup
            if allnodes.index(n) + 1 == len(allnodes):
                for e in etcds:
                    backupcmd = 'ssh ' + acc + '@' + e + ' sudo /opt/bin/etcdctl \
                                backup --data-dir ' + etcddatapath + ' --backup-dir \
                                ' + etcdbackuppath + '.' + time.strftime("%Y%m%d%H%m", time.localtime())
                    deploy.connect_using_pexpect(e, backupcmd, acc, passwd)

        elif cmd == 'deploy' :
            # kubernetes service down
            res = False
            while res == False:
                deploy.cmd_service(n, 'stop', 'flanneld', acc, passwd)
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
