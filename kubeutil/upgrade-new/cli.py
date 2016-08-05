#!/usr/bin/python
#-*- coding:utf-8 -*-

import os,sys
from clustermanager import ClusterMgr

def print_info():
    print "Cluster Manager CLI V0.1"
    
def print_help():
    cmddict = {'exit':'exit cli', 'list':'to listing clusters', 'create':'create clustermanager' , 'export':'export infomation'}
    print "cli usage"
    print "> cmd args"
    for k in cmddict.keys():
        print("   %s : %s" %(k, cmddict[k]))

if __name__=='__main__':
#cluster manager cli
# cluster manager object data structure : tree
    print_info()

    while True:
        var = raw_input("> ")
        #print(var)
        if var == 'exit':
            sys.exit(1)
        elif var == 'create':
            cm = ClusterMgr()
            cm.set_cluster('kube1')
        elif var == 'export':
            cm.export_config()
            cm.export_svc()
            cm.export_etcd()
        elif var == 'upgrade':
            cm.upgrade()
        elif var == 'install':
            cm.install()
        elif var == 'list':
            pass 
        elif var == '':
            pass 
        elif var == 'help':
            print_help()    
        else:
            #sys.exit(1)
            print("Plz check the cmd")
