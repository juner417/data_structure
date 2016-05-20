#!/usr/bin/python
# -*- coding:utf-8 -*-

import os, sys
import logging, time, re, subprocess, pexpect
import simplejson, urllib2
import common

'''
Description:
 To deploy k8s binary 
 file indent = space(4)
'''

logging.basicConfig(level=logging.DEBUG,
                    format='[%(asctime)s][%(levelname)s] %(message)s')

def export_kube_conf(target, confpath, backuppath, acc, passwd=None):
    msg = 'Are you sure you want to continue connecting'
    dirfullpath = os.path.join(os.path.dirname(os.path.abspath(__file__)), backuppath, target)

    if os.path.isdir(dirfullpath) is False:
        os.makedirs(dirfullpath)
  
    child = pexpect.spawn('scp -r ' + acc + '@' + target + ':' + confpath + '/kube*' + ' ' + 
                           dirfullpath + '/')
    index = child.expect([msg, 'password:', pexpect.EOF, pexpect.TIMEOUT])

    if index == 0 : 
        child.sendline('yes')
        index = child.expect([msg, 'password:', pexpect.EOF, pexpect.TIMEOUT])

    if index == 1:
        child.sendline(passwd)
        child.expect(pexpect.EOF)
        return True
    elif index == 2:
        logging.info('%s kubeconfs are now exporting' %(target)) 
        child.after
        return True
    else:
        logging.error('cannot connect to %s' % target)
        return False

def connect_using_pexpect(target, cmd, acc, passwd=None):
    # make connection do something on remote host
    msg = 'Are you sure you want to continue connecting'
    child = pexpect.spawn('/bin/bash', ['-c', cmd])
    index = child.expect([msg, 'password:', pexpect.EOF, pexpect.TIMEOUT])

    if index == 0 :
        child.sendline('yes')
        index = child.expect([msg, 'password:', pexpect.EOF, pexpect.TIMEOUT])

    if index == 1:
        logging.info('%s server is require passwd to login - %s' % (target,cmd))
        child.sendline(passwd)
        child.expect(pexpect.EOF)
        res = True
    elif index == 2:
        logging.info('%s server is NOT require passwd to login - %s' % (target,cmd))
        child.after
        res = True
    else:
        logging.error('connot connect to %s' % target)
        res = False
    return res, child.before.strip('\n')

def deploy_kube_bin(target, sourcepath, targetpath, role, acc, passwd=None):
    # deploy new binary 
    msg = 'Are you sure you want to continue connecting'
    sourcefullpath = os.path.join(sourcepath, role)
    #print(sourcefullpath)
    #cmd = 'scp -r ' + sourcefullpath + '/kube*' + ' ' + acc + '@' + target + ':/tmp/' 
    cmd = 'scp -r ' + sourcefullpath + '/' + ' ' + acc + '@' + target + ':/tmp/' 
    res, out = connect_using_pexpect(target, cmd, acc, passwd)
    copycmd = 'ssh ' + acc +'@'+ target + ' sudo cp /tmp/'+ role + '/kube* ' + targetpath + '/'
    cres, cout = connect_using_pexpect(target, copycmd, acc, passwd) 
    print(cout)
    return cres

def get_api(url):
    # get api result
    try: 
        res = simplejson.load(urllib2.urlopen(url))
    except urllib2.HTTPError as err:
        logging.error(err - url)
        sys.exit(2)
    except urllib2.URLError as err:
        logging.error(err - url)
        sys.exit(2)
    return res

def get_kube_version(jsondict, role, comp):
    # get kube binary version
    verdict = {}
    if role == 'master': 
        keys = jsondict.keys()
        for i in comp:
            verdict[i] = jsondict['gitVersion'].strip('v')
    elif role == 'nodes':
        keys = jsondict['status']['nodeInfo'].keys()
        for i in comp:
            verdict[i] = jsondict['status']['nodeInfo'][i+'Version'].strip('v')
    return verdict

def get_docker_version(target, acc, passwd=None):
    # get target docker version 
    # 지금은 docker tcp가 localhost로 열려 있어서 docker 커맨드를 직접입력 후 확인
    # 나중에 변경 필요 api 호출로(get_api 사용)
    runcmd = 'ssh ' + acc + '@' + target + ' \"docker version | grep \"Version\" | \
              sort | uniq | awk \'{print \$2}\'\"'
    res, version = connect_using_pexpect(target, runcmd, acc, passwd)
    return version

def get_node_ip(target):
    # search node ip in /etc/hosts
    target_ip = None
    f = open('/etc/hosts' , 'r')
    lines = f.readlines()
    for line in lines:
        if re.search(target, line):
            target_ip = line.split()[0]
    return target_ip

def diff_kube_version(target, apiserver, exversion, role):
    version_dict = {}
    ip_dict = {}
    res = None
    target_ip = None

    target_ip = get_node_ip(target)
    if target_ip is None:
        logging.error('Host : %s is not in /etc/hosts file. Plz check the hosts file' % target)
        sys.exit(2) 
     
    if role == 'master': 
        binary = ['kube-apiserver', 'kube-controller-manager', 'kube-scheduler']
        url = 'http://' + apiserver + '/version'
    else:
        binary = ['kubelet', 'kubeProxy']
        url = 'http://' + apiserver + '/api/v1/nodes/' + target_ip

    version_dict = get_kube_version(get_api(url), role, binary)
    for i in version_dict.values():
        if exversion == i: 
            res = True
        else :
            res = False
            break
    return res

def diff_docker_version(target, exversion, confversion, acc, passwd=None):
    # compare between docker versions 
    try: 
        docker_version = get_docker_version(target, acc, passwd).strip('\r')
    except:
        logging.error('Cannot get the docker version in %s' % (target))
    
    if docker_version == confversion:
        # normal status
        res = True
    else:
        # need to upgrade
        # docker_version is not same with confversion or weird
        res = False
    return res, docker_version
    
def check_service(target, cmd, acc, passwd=None):
    # check the kube services
    runcmd = 'ssh ' + acc + '@' + target + ' ' + cmd

    res, out = connect_using_pexpect(target, runcmd, acc, passwd)
    if int(out) >= 2:
        logging.info('%s server, kubernetes is now running - proc : %s' % (target, out))
        return True
    else:
        logging.error('%s server, kubernetes is not working - proc : %s' % (target, out))
        return False

def cmd_service(target, action, svcnm, acc, passwd=None):
    # service start/stop
    runcmd = 'ssh ' + acc + '@' + target + ' ' + '\" sudo service \"' + svcnm + ' ' + action 
    i = 0
    res = False
    while res == False:
        res, out = connect_using_pexpect(target, runcmd, acc, passwd)
        i += 1
        if i > 3 and res == False:
            logging.error('%s - %s service cannot %s ' %(target, svcnm, action))
            sys.exit(2)

def install_docker(target, version, srcpath, acc, passwd=None):   
    # to intall docker
    copycmd = 'scp ' + srcpath + ' ' + acc + '@' + target + ':/tmp/'  
    instcmd = 'ssh ' + acc + '@' + target + ' \" sudo dpkg -i /tmp/\"' + os.path.split(srcpath)[1]   
    
    i = 0
    cres = False
    ires = False
    while cres == False:
        cres, cout = connect_using_pexpect(target, copycmd, acc)
        if cres == True:
            #ires, iout = connect_using_pexpect(target, instcmd, acc)
            child = pexpect.spawn('/bin/bash', ['-c', instcmd])
            child.expect('[default=N] ?')
            child.sendline('N')
            child.expect(pexpect.EOF)
            ires = get_docker_version(target, acc)
            if ires == False:
                cres = False
                i += 1
                if i > 3 :
                    logging.error('%s-v%s connot install docker' %(target, version))
                    sys.exit(2)

if __name__=='__main__':

    ini_file = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'config.ini')
