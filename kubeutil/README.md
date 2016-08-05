# kubeutils

## kubeutils/upgrade/upgrade.py

<hr>

* [**useage**]
```bash
$ python upgrade.py -c config -m action -h host(optional-default:all) -l cluster_name(optional-default:all)
```

* [**download**]
```bash
$ git clone git@172.19.136.46:kubernetes/kubeutils.git
$ cd upgrade
$ python upgrade.py -c config.ini -m export 
...
```

* [**source**]
  - cluster.py : cluster class
  - common.py : common function
  - config.ini : upgrade config 
  - upgrade.py : upgrade run cli

* [**기능들...(-m)**]

## export  
 - logic:
   - 노드 별 kubernetes config("/etc/default/kube") backup경로에 config를 localdir(config, backupdir)에 backup
   - etcd snapshot 데이터 backup경로에 backup
   - 현재 클러스터의 svc, rc, deployments등 config에 지정한 서비스 backup

## kube_upgrade 
 - logic:
   - 노드에 kubernetes 서비스 종료
   - 지정한 버전(config.ini)의 kubernetes 바이너리 배포
   - 노드에 kubernetes 서비스 시작

## kube_rollback 
 - logic:
   - 노드에 kubernetes 서비스 종료
   - upgrade 이전 버전(config.ini)의 kubernetes 바이너리 배포
   - 노드에 kubernetes 서비스 시작

## docker_upgrade 
 - logic :
   - 노드에 설치된 버전 확인
   - config.ini 에서 지정한 버전이랑 맞는지 확인
   - 다르면 지정한 버전으로 설치
   - 같으면 그냥 넘어감

## docker_rollback 
 - logic :
   - 노드에 설치된 버전 확인
   - upgrade 이전버전의 docker와 버전이 같으면 그냥 넘어감
   - 버전이 다르면 이전 버전 설치 

## 추가할 기능
 - 설치(init)
 - 배포 
 - config 수정
