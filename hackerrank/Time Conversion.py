#!/bin/python3

import os
import sys

#
# Complete the timeConversion function below.
#
def timeConversion(s):
    if s[-2:]=="AM":
        if s[0:2]=="12":
            return "00"+s[2:-2]
        else: 
            return s[0:-2]
    else:
        if s[0:2]=="12":
            return "12"+s[2:-2]
        else:
            return str(int(s[0:2])+12)+s[2:-2]

if __name__ == '__main__':
    f = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = timeConversion(s)

    f.write(result + '\n')

    f.close()
