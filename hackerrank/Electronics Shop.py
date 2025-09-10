#!/bin/python3

import os
import sys

#
# Complete the getMoneySpent function below.
#
def getMoneySpent(keyboards, drives, b):
    mink = mind = 10**6

    for i in keyboards:
        if i < mink:
            mink = i

    for i in drives:
        if i < mind:
            mind = i
    min = mink + mind
    if b < min:
        return -1
    else:
        spent = 0
        for i in keyboards:
            for j in drives:
                if i+j <= b and i+j>spent:
                    spent = i+j
    return spent


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    bnm = input().split()

    b = int(bnm[0])

    n = int(bnm[1])

    m = int(bnm[2])

    keyboards = list(map(int, input().rstrip().split()))

    drives = list(map(int, input().rstrip().split()))

    #
    # The maximum amount of money she can spend on a keyboard and USB drive, or -1 if she can't purchase both items
    #

    moneySpent = getMoneySpent(keyboards, drives, b)

    fptr.write(str(moneySpent) + '\n')

    fptr.close()
