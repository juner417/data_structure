#-*- coding: utf-8 -*-
#!/usr/bin/python
# file indent: space(4)

def isPalindrome(len, str):
    
    for i in xrange(len/2):
        if str[i] != str[len-1-i]:
            return False
        
    return True

# palindrome인지 판단 
if __name__=='__main__':

    case = input()

    for i in xrange(case):
        length, str = raw_input().split(" ")

    res = isPalindrome(int(length), str)

    if res:
        print("palindrome true")
    else:
        print("palindrome FALSE")
