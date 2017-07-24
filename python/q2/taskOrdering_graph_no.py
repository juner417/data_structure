#-*- coding: utf-8 -*-
#!/usr/bin/python
# file indent : space(4)

import sys, string
import Queue as Q

# Q2 Task Ordering
# topology sorting
# elapsed time : 2H
'''
 제출 후 고친내용
 1. input/output prompt
 2. while 문 제거(runtime error)
 3. range -> xrange (memory사용량이 적음)
 4. case입력 받을 때 input 사용 (int 형변환 안해도 됨)
 5. tasks string.ascii_uppercase/lowercase 변경 (task에 특수 문자 들어갔음)
 처음에는 itertools.permutations 모든 조합을 구해 dependency에 맞는것만 골라내려 했으나 너무 오래 걸림

 Q1. 왜 우선순위 큐를 사용했나? -> 사전순으로 가장 앞의 것을 찾기 위해
 Q2. BFS 를 좀더 구현해 보자 -> 이건 BFS에 더 가깝다. 
'''

class Graph(object):

    def __init__(self, task):
        self.head = 0
        self.tail = []
        self.task = task

if __name__=='__main__':

    # insert prioity queue cuz alphabet order
    que = Q.PriorityQueue()
    # input case count
    case = input()

    # verify the number of cases
    if case > 50 or case <= 0:
        print("Plz, check the case count(your's :%s)" % case)
        exit(1)

    # input task and dependency
    for i in xrange(0, case):
        task_dict = {}
        tasks_cnt, depend = raw_input().split()
        tasks = string.ascii_uppercase + string.ascii_lowercase
       
        # create the tasks object(A,B,...)
        for i in tasks[0:int(tasks_cnt)]:
            task_dict[i] = Graph(i)

        # set dependency
        for i in xrange(0, int(depend)):
            n = raw_input()
            pre = n[0]
            post = n[1]

            task_dict[pre].tail.append(task_dict[post])
            task_dict[post].head += 1

        # insert a task 0 head in prioity queue 
        for i in task_dict.keys():
            if task_dict[i].head == 0:
                que.put(task_dict[i].task)

        res = '' # task order result
        # get a pre tasks in queue
        while not que.empty():
            g = que.get()
            res += g
            
            # find a post task and put it 
            for i in task_dict[g].tail:
                i.head -= 1
                if i.head == 0:
                    que.put(i.task) 

        print(res)
