#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the flatlandSpaceStations function below.
def flatlandSpaceStations(n, c):
    c = sorted(c)
    distances = []
    if len(c) > 1:
        for s1, s2 in zip(c, c[1:]):
            distances.append(s2 - s1)
        return max([max(distances) // 2, n - c[-1] - 1, c[0]])
    return max([n - c[-1] - 1, c[0]])

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    c = list(map(int, input().rstrip().split()))

    result = flatlandSpaceStations(n, c)

    fptr.write(str(result) + '\n')

    fptr.close()
