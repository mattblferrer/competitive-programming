#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'funnyString' function below.
#
# The function is expected to return a STRING.
# The function accepts STRING s as parameter.
#

def funnyString(s):
    diff1, diff2 = [], []
    for c1, c2 in zip(s, s[1:]):
        diff1.append(abs(ord(c1) - ord(c2)))
    s = s[::-1]
    for c1, c2 in zip(s, s[1:]):
        diff2.append(abs(ord(c1) - ord(c2)))
        
    if diff1 == diff2:
        return "Funny"
    return "Not Funny"

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        s = input()

        result = funnyString(s)

        fptr.write(result + '\n')

    fptr.close()
