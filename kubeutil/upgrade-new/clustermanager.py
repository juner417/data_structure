#!/usr/bin/python
#-*- coding:utf-8 -*-

import os, sys, logging
from cluster import Cluster

'''
Description:
  k8s clustermanager object
  file indent = space(4)
'''
logging.basicConfig(level=logging.INFO,
     format='[%(asctime)s][%(levelname)s] %(message)s')

class ClusterMgr(object):

    _clusterPlatform = None
    _clusterList = []
    _clusterStatus = {}
    ini_file = None

    def __init__(self):
        self.ini_file = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'config.ini.new')

    def get_cluster(self):
        for c in self._clusterList:
            print(c.get_clusternm)

    def set_cluster(self, clusternm):
        # add a cluster object in _clusterList
        self._clusterList.append(Cluster(self.ini_file, clusternm))

    def init_cluster(self, cluster):
        # cluster info initiation
        for c in self._clusterList:
            installed = c.get_init()

    def check_cluster(self):
        # check the cluster status 
        pass

    def install(self):
        # install a cluster
        for c in self._clusterList:
            c.do_install()

    def export_config(self):
        # export cluster configs
        for c in self._clusterList:
            c.do_export_conf()

    def export_svc(self):
        for c in self._clusterList:
            c.do_export_svc()

    def export_etcd(self):
        for c in self._clusterList:
            c.do_backup_etcd()

    def upgrade(self):
        # upgrade cluster
        for c in self._clusterList:
            clusternm = c.get_clusternm()
            #c.set_cur_version()
            res = c.do_upgrade_cluster()
            logging.info('%s cluster upgrade result : %s' %(clusternm, res))

    def rollback(self):
        # rollback cluster
        for c in self._clusterList:
            c.ch_cluster_version(prever)
