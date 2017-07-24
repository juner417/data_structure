#-*- coding: utf-8 -*-
#!/usr/bin/python
# file indent : space(4)

import sys
# Q1 Text Encryption
# sort a text by even, odd
# elapsed time : 12m

def encryptor(text):
    # even + odd
    return text[::2] + text[1::2]

if __name__=='__main__':

    input_cnt = int(raw_input("input count(1-10)> "))

    # verify a count
    if input_cnt > 10 or input_cnt <= 0:
        print("Plz check the input count(your's: %s) " % (
            input_cnt))
        exit(1)

    # input texts
    for i in range(0, input_cnt):
        input_text = raw_input("> ")[:100]

        # remove spaces
        input = input_text.replace(" ", "")

        # to encrypt the set of texts
        res = encryptor(input)
        print(res)
