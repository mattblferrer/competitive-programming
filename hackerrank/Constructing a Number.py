#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'canConstruct' function below.
#
# The function is expected to return a STRING.
# The function accepts INTEGER_ARRAY a as parameter.
#

def canConstruct(a):
    # Return "Yes" or "No" denoting whether you can construct the required number.
    if sum(sum(int(d) for d in str(i)) for i in a) % 3 == 0:
        return "Yes"
    return "No"

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input().strip())

    for t_itr in range(t):
        n = int(input().strip())

        a = list(map(int, input().rstrip().split()))

        result = canConstruct(a)

        fptr.write(result + '\n')

    fptr.close()
