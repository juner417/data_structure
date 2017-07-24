#!/usr/bin/python

def findLongestPalindromicString(text):
    N = len(text)
    if N == 0:
        return
    N = 2*N+1    # Position count
    L = [0] * N
    L[0] = 0
    L[1] = 1
    C = 1     # centerPosition
    R = 2     # centerRightPosition
    i = 0    # currentRightPosition
    iMirror = 0     # currentLeftPosition
    maxLPSLength = 0
    maxLPSCenterPosition = 0
    start = -1
    end = -1
    diff = -1
  
    # Uncomment it to print LPS Length array
    # printf("%d %d ", L[0], L[1]);
    for i in xrange(2,N):
      
        # get currentLeftPosition iMirror for currentRightPosition i
        iMirror = 2*C-i
        L[i] = 0
        diff = R - i
        # If currentRightPosition i is within centerRightPosition R
        if diff > 0:
            L[i] = min(L[iMirror], diff)
  
        # Attempt to expand palindrome centered at currentRightPosition i
        # Here for odd positions, we compare characters and
        # if match then increment LPS Length by ONE
        # If even position, we just increment LPS by ONE without
        # any character comparison
        try:
            while ((i + L[i]) < N and (i - L[i]) > 0) and \
                    (((i + L[i] + 1) % 2 == 0) or \
                    (text[(i + L[i] + 1) / 2] == text[(i - L[i] - 1) / 2])):
                L[i]+=1
        except Exception as e:
            pass
  
        if L[i] > maxLPSLength:        # Track maxLPSLength
            maxLPSLength = L[i]
            maxLPSCenterPosition = i
  
        # If palindrome centered at currentRightPosition i
        # expand beyond centerRightPosition R,
        # adjust centerPosition C based on expanded palindrome.
        if i + L[i] > R:
            C = i
            R = i + L[i]
  
    # Uncomment it to print LPS Length array
    # printf("%d ", L[i]);
    start = (maxLPSCenterPosition - maxLPSLength) / 2
    end = start + maxLPSLength - 1
    print "LPS of string is " + text + " : ",
    print text[start:end+1],
    print "\n",

def longestPalindrome(s):
    # Transform S into T.
    # For example, S = "abba", T = "^#a#b#b#a#$".
    # ^ and $ signs are sentinels appended to each end to avoid bounds checking
    T = '#'.join('^{}$'.format(s))
    n = len(T)
    P = [0] * n
    C = R = 0
    for i in range (1, n-1):
	P[i] = (R > i) and min(R - i, P[2*C - i]) # equals to i' = C - (i-C)
	# Attempt to expand palindrome centered at i
	while T[i + 1 + P[i]] == T[i - 1 - P[i]]:
	    P[i] += 1

	# If palindrome centered at i expand past R,
	# adjust center based on expanded palindrome.
	if i + P[i] > R:
	    C, R = i, i + P[i]

    # Find the maximum element in P.
    maxLen, centerIndex = max((n, i) for i, n in enumerate(P))
    #return s[(centerIndex  - maxLen)//2: (centerIndex  + maxLen)//2]
    print s[(centerIndex  - maxLen)//2: (centerIndex  + maxLen)//2]
    #print maxLen/2 + 1
    print P

if __name__=='__main__':
    
    str = raw_input()    
    findLongestPalindromicString(str)
    longestPalindrome(str)
