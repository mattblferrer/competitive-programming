#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'hourglassSum' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY arr as parameter.
#

def hourglassSum(arr):
    maximum_sum = float("-inf")
    
    for i in range(4):
        for j in range(4):
            a = arr[i][j]
            b = arr[i][j + 1]
            c = arr[i][j + 2]
            d = arr[i + 1][j + 1]
            e = arr[i + 2][j]
            f = arr[i + 2][j + 1]
            g = arr[i + 2][j + 2]
            
            hourglass_sum = sum([a, b, c, d, e, f, g])
            if hourglass_sum > maximum_sum:
                maximum_sum = hourglass_sum
                
    return maximum_sum
        

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    arr = []

    for _ in range(6):
        arr.append(list(map(int, input().rstrip().split())))

    result = hourglassSum(arr)

    fptr.write(str(result) + '\n')

    fptr.close()
