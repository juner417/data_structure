#-*- coding: utf-8 -*-
#!/usr/bin/python
# file indent : space(4)

import sys
# Q1 Text Encryption
# sort a text by even, odd
# elapsed time : 12m
'''
 제출 후 고친 내용 
 1. input/output prompt
'''
def encryptor(text):
    # even + odd
    return text[::2] + text[1::2]
    # Q1) 만약 python array slice 기능을 안썼다면...
    # even, odd = ""
    # for i, v in enumerate(text):
    #     if i % 2 == 0:
    #         even = even + v
    #     elif i % 2 != 0:
    #         odd = odd + v
    # print(even+odd)

if __name__=='__main__':

    input_cnt = int(raw_input())

    # verify a count
    if input_cnt > 10 or input_cnt <= 0:
        print("Plz check the input count(your's: %s) " % (
            input_cnt))
        exit(1)

    # input texts
    for i in range(0, input_cnt):
        input_text = raw_input()[:100]

        # remove spaces
        input = input_text.replace(" ", "")

        # to encrypt the set of texts
        res = encryptor(input)
        print(res)
