h3. kubeutil

kubeutil

start.py
 - useage
$ python start.py -c config -m action -h host

- deploy.py
- common.py
- config.ini 


기능들...(-m)
export : 
 - logic:
   # 노드 별 kubernetes config("/etc/default/kube") backup경로에 backup
   # etcd snapshot 데이터 backup경로에 backup
deploy :
 - logic:
   # 노드에 kubernetes 서비스 종료
   # 지정한 버전(config.ini)의 kubernetes 바이너리 배포
   # 노드에 kubernetes 서비스 시작
docker
 - logic :
   # 노드에 설치된 버전 확인
   # config.ini 에서 지정한 버전이랑 맞는지 확인
   # 다르면 지정한 버전으로 설치
   # 같으면 그냥 넘어감
rollback 
 - logic : 
   # 설치된 바이너리 버전 확인
   # 만약 버전이 다르고 cofig에 이전 버전보다 높을 경우 롤백대상
   # rollback 대상 서버 서비스 shutdown
   # 버전 배포 
   # 서비스 재시작
  
