#-*- coding: utf-8 -*-
#!/usr/bin/python
# file indent : space(4)

import sys

# Q3 Count Palindrome
# manacher's algorithm 
# elapsed time : 3H

def searchPalin(length, text):

    results = set()
    for idx, char in enumerate(text):
        # find a longest odd palindrome
        start, end = idx - 1, idx + 1
        while start >= 0 and end < length and text[start] == text[end]:
            results.add(text[start:end+1])
            start -= 1
            end += 1
        # find a longest even palindrome
        start, end = idx, idx + 1
        while start >= 0 and end < length and text[start] == text[end]:
            results.add(text[start:end+1])
            start -= 1
            end += 1

    return list(results)

if __name__=='__main__':

    while True:
        # input the number of cases
        case = int(raw_input("#inputString> "))

        # verify the number of cases
        if case > 50 or case <= 0:
            print("Plz, check the cases count")
            continue

        for i in range(0, case):
            length, input_str = raw_input(
                "#text text> ").split(" ")

            if int(length) != len(input_str):
                print("Plz, check the args")
                continue

            res = searchPalin(int(length), input_str)
            print(len(res))
            print(res)

