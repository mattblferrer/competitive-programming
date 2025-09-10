#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the miniMaxSum function below.
def miniMaxSum(arr):
    min = 10**9
    max = 0
    sum = 0
    for i in range(0,5):
        if arr[i] > max:
            max = arr[i]
        if arr[i] < min:
            min = arr[i]
        sum += arr[i]
        
    print(str(sum-max)+" "+str(sum-min))

if __name__ == '__main__':
    arr = list(map(int, input().rstrip().split()))

    miniMaxSum(arr)
