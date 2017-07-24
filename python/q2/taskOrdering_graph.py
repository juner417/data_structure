#-*- coding: utf-8 -*-
#!/usr/bin/python
# file indent : space(4)

import sys
import Queue as Q

# Q2 Task Ordering
# topology sorting
# elapsed time : 2H

class Graph(object):

    def __init__(self, task):
        self.head = 0
        self.tail = []
        self.task = task

if __name__=='__main__':

    while True:
        # insert prioity queue cuz alphabet order
        que = Q.PriorityQueue()
        # input case count
        case = int(raw_input("The number of case> "))

        # verify the number of cases
        if case > 50 or case <= 0:
            print("Plz, check the case count(your's :%s)" % case)
            continue

        # input task and dependency
        for i in range(0, case):
            task_dict = {}
            tasks, depend = raw_input(
                "#task #depend> ").split(" ")
           
            # create the tasks object(A,B,...)
            for i in range(65, 65+int(tasks)):
                task_dict[chr(i)] = Graph(chr(i))

            # set dependency
            for i in range(0, int(depend)):
                n = raw_input("depend> ")
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
