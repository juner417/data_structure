#!/usr/bin/python
# -*- coding:utf-8 -*-

import os, sys
import logging, time, re, ConfigParser
import common, cluster

'''
Description:
 To deploy k8s binary 
 file indent = space(4)
'''

if __name__=='__main__':

    logging.basicConfig(level=logging.DEBUG,
                    format='[%(asctime)s][%(levelname)s] %(message)s')
    try:
        ini_file, cmd, host, targetcluster = common.read_opt()
        # get cluster names
        config = ConfigParser.ConfigParser()
        config.read(ini_file)
    except:
        common.print_usage()

    if targetcluster is None:
        clusternms = config.sections()
        clusternms.remove('upgrade')   
    else:
        clusternms = [targetcluster] 
 
    clusters = []
    for c in range(0,len(clusternms)): 
        # create cluster object in clusters array
        clusters.append(cluster.Cluster(ini_file, clusternms[c]))
  
    for cl in clusters: 
        role = {}
        master = cl.get_master
        nodes = cl.get_nodes
    
        for i in nodes:
            role[i] = "minion"
        for i in master:
            role[i] = "master"
    
        if host is None:
            allnodes = nodes + master
        else:
            allnodes = [host]
    
        for n in allnodes:
            node_role = role.get(n)
    
            if cmd == 'export' :
                try:
                    cl.export_kube_conf(n)
                except Exception, e:
                    logging.error('export kubernetes config is fail : %s - %s' % (n, e))
    
                # etcd snapshot backup, last node
                if allnodes.index(n) + 1 == len(allnodes):
                    cl.backup_etcd()
                    cl.export_kube_svc()
    
            elif cmd == 'kube_upgrade' or cmd == 'kube_rollback' : 
                # kubernetes binary rollback
                if cmd == 'kube_upgrade': 
                    curv = cl.get_kube_cur_version 
                    nextv = cl.get_kube_next_version 
                else:
                    curv = cl.get_kube_next_version
                    nextv = cl.get_kube_cur_version 

                res = cl.check_kube_version(n, node_role, nextv)
                if res == True:
                    logging.info('%s kube binary version is same it\'s specified (v%s)' %(n, nextv ))
                else:
                    logging.info('%s kube binary are now deployed (v%s -> v%s)' %(n, curv, nextv))
                    while res == False:
                        logging.info('%s node - %s' %(n, cmd))
                        cl.send_cmd_to_server(n, 'flanneld', 'stop')
                        time.sleep(2) 
                        cl.deploy_kube_bin(n, node_role, cmd)
                        time.sleep(3) 
                        cl.send_cmd_to_server(n, 'flanneld', 'start' )
                        res = cl.check_service(n, 'ps -ef | grep /opt/bin/kube | grep -v grep | wc -l')
    
            elif cmd == 'docker_upgrade' or cmd == 'docker_rollback' :
                # docker upgrade/downgrade
                # classify node roll
                if node_role == 'master':
                    res = True
                    checkversion = 'master'
                else:
                    # specify a docker version 
                    if cmd == 'docker_upgrade':
                        curv = cl.get_docker_cur_version
                        nextv = cl.get_docker_next_version
                    else:
                        curv = cl.get_docker_next_version
                        nextv = cl.get_docker_cur_version
                    # check the current docker version 
                    res, checkversion = cl.check_docker_version(n, nextv)
          
                if res == True :
                    logging.info('%s node - the docker version is what you need (v%s)' %
                                 (n, checkversion))
                else:
                    # false : the docker version differece with your specified
                    logging.info('%s node - need to install docker version : %s -> %s' % 
                                 (n, checkversion, nextv)) 

                    kube_newv = cl.get_kube_next_version
                    kube_version = cl.check_kube_version(n, node_role, kube_newv)
                    kube_cur_version = cl.get_kube_check_version

                    if int(kube_cur_version['kubelet'].split('.')[1]) == 2:
                        # drain the target using kubectl
                        # after that be changed using kubectl proxy api
                        node_ip = cl.get_node_ip(n)
                        apiserver = cl.get_apiserver
                        deploym = cl.get_deploy
                        draincmd = '/opt/bin/kubectl -s http://' + apiserver + ' \
drain ' + node_ip + ' --force'
                        res = False
                        while res == False:
                            res,out = cl.connect_using_pexpect(deploym, draincmd)
                            if res is True:
                                logging.info('%s node - now drain' % (n ))
                            else: 
                                logging.error('%s drains fail, You better check the machine status' % n)
                    else:
                        # aint got no drain function
                        res = True
                        while res == True:
                            cl.send_cmd_to_server(n, 'flanneld', 'stop')
                            time.sleep(2)
                            res = cl.check_service(n, 'ps -ef | grep /opt/bin/kube | grep -v grep | wc -l')

                            if res == True:
                                logging.warn('%s node - kubelet proc is now running' % n)
                            else:
                                logging.info('%s node - kubelet proc is stop' % n)

                    # install docker 
                    cl.install_docker(n, nextv)
                    time.sleep(2)
                    version_flag, version = cl.check_docker_version(n, nextv)

                    if version_flag == True:
                        logging.info('%s node - the docker version is what you need(v%s)' % (n, nextv))
                    else:
                        logging.error('%s node - the docker version is not same you need(%s -> %s' 
                                      % (n, version, nextv))
    
                    # service start
                    if int(kube_cur_version['kubelet'].split('.')[1]) == 2:
                        # drain the target using kubectl
                        # after that be changed using kubectl proxy api
                        node_ip = cl.get_node_ip(n)
                        apiserver = cl.get_apiserver
                        uncordoncmd = '/opt/bin/kubectl -s http://' + apiserver + ' uncordon ' + node_ip

                        res = False
                        while res == False:
                            res,out = cl.connect_using_pexpect(deploym, uncordoncmd)
                            if res is True:
                                logging.info('%s node - now normal status' % n)
                            else:
                                logging.error('%s uncordon fail, You better check the machine status' % n)
                    else:
                        # no drain function
                        res = False
                        while res == False:
                            cl.send_cmd_to_server(n, 'flanneld', 'start')
                            time.sleep(2)
                            res = cl.check_service(n, 'ps -ef | grep /opt/bin/kube | grep -v grep | wc -l')
                            if res == True:
                                logging.info('%s node - kubelet proc is now running' % n)
                            else:
                                logging.error('%s node - kubelet proc cannot start' % n)
                        
                
            elif cmd == 'scaleout':
                logging.warn('%s cmd is under construction' %(cmd))
                #노드 확장... 
                if cl.get_clusterplatform == 'openstack':
                    #cl.scaleout_node()
                    print(cl.get_cluasterplatform)
                else:
                    print('%s platform are not support' %(cl.get_clusterplatrom))
                    sys.exit(1)
            elif cmd == 'deploy':
                cl.deploy_kube_bin(n, node_role, cmd)
                cl.send_cmd_to_server(n, 'flanneld', 'restart')
               
            else:
                logging.warn('%s is not cmd' % (cmd))
                common.print_usage()
                sys.exit(1)
            time.sleep(3)
