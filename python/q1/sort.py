#-*- coding: utf-8 -*-
#!/usr/bin/python
# file indent space(4)

def selectionSort(list):
   
    i = 0
    j = 0
    min = 0

    for j in xrange(len(list)):
        min = j
        i = j + 1

        while i < len(list):
            if list[min] > list[i]:
                list[min], list[i] = list[i], list[min]

            i += 1

    return list

def insertSort(list):
    
def bubbleSort(list):
    pass


if __name__=='__main__':
    
    a = [ 3, 4, 6, 7, 1, 2, 5, 9, 8]

    sres = selectionSort(a[:])
    #bres = bubbleSort(a)

    print(a)
    print(sres)
    #print(bres)
