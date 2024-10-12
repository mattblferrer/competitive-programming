#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'kaprekarNumbers' function below.
#
# The function accepts following parameters:
#  1. INTEGER p
#  2. INTEGER q
#

def kaprekarNumbers(p, q):
    kaprekars = ""
    for i in range(p, q + 1):
        sqr = i ** 2
        length = len(str(sqr)) // 2
        r = int(str(sqr)[length:])
        l = str(sqr)[:length]
        if l: 
            l = int(l)
        else:
            l = 0
        
        if r + l == i:
            kaprekars += str(i) + " "
    if kaprekars:
        print(kaprekars)
    else:
        print("INVALID RANGE")

if __name__ == '__main__':
    p = int(input().strip())

    q = int(input().strip())

    kaprekarNumbers(p, q)
