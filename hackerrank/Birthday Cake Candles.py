#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the birthdayCakeCandles function below.
def birthdayCakeCandles(ar):
    max = 0
    ctr = 0
    for i in range(0,len(ar)):
        if ar[i]>max:
            max = ar[i]
    for i in range(0,len(ar)):
        if ar[i]==max:
            ctr+=1
    return ctr

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    ar_count = int(input())

    ar = list(map(int, input().rstrip().split()))

    result = birthdayCakeCandles(ar)

    fptr.write(str(result) + '\n')

    fptr.close()
