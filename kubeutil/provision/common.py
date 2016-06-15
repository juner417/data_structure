#!/usr/bin/python
# -*- coding: utf-8 -*-

import os, sys, ConfigParser, getopt

def print_usage():

    print ('WARN) check the args')
    print ('USAGE) python %s -c config_file -m action -h host(optional) -l clusterName(optional)' 
          % (sys.argv[0]))
    print ('  [action]: kube_upgrade, kube_rollback, export, docker_upgrade, docker_rollback, scaleout')
    sys.exit(1)


def config_map(filename,section):
    fnm = filename
    config = ConfigParser.ConfigParser()
    config.read(fnm)
    options = config.options(section)
    config_dict = {}
    
    for option in options:
        try:
            config_dict[option] = config.get(section, option)
            if config_dict[option] == -1:
              DebugPrint("skip: %s" % option)
        except:
            print("exception on %s " % option)
            config_dict[option] = None
    return config_dict

def read_opt():

    configfile = None
    cmd = None
    host = None
    clusternm = None
    try:
        opt, args = getopt.getopt(sys.argv[1:], 'c:m:h:l:')
    except getopt.GetoptError as err:
        print_usage()
        sys.exit(2)
    
    for op, p in opt:
        if op == '-c':
        # config option
            configfile = p
        elif op == '-m':
        # command option
            cmd = p
        elif op == '-h':
            host = p
        elif op == '-l':
            clusternm = p
        else:
            print_usage()
            sys.exit(2)
    return configfile, cmd, host, clusternm
    
