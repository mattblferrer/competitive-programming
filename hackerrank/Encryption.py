#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the encryption function below.
def encryption(s):
    s = s.replace(" ","")
    rows = math.floor(math.sqrt(len(s)))
    cols = math.ceil(math.sqrt(len(s)))
    if len(s)>rows*cols:
        rows+=1
    s = s+rows*" "
    output = ""

    for i in range(0,cols):
        for j in range(0,rows):
            if s[(j*cols)+i]!=" ":
                output+=s[(j*cols)+i]
        output+=" "
    return output

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = encryption(s)

    fptr.write(result + '\n')

    fptr.close()
