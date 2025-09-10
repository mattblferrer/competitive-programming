#!/bin/python3

import os
import sys
import math

#
# Complete the pageCount function below.
#
def pageCount(n, p):
    if n%2==1:
        n = n-1
    if p%2==1:
        p = p-1
    if (n-p)/2 > p/2:
        return int(p/2)
    else:
        return int((n-p)/2)
    

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    p = int(input())

    result = pageCount(n, p)

    fptr.write(str(result) + '\n')

    fptr.close()
