#!/bin/python3

import math
import os
import random
import re
import sys



if __name__ == '__main__':
    n = int(input().strip())
    binary = bin(n)[2:]
    run_length = 0
    max_run_length = 0
    for digit in binary:
        if digit == "1":
            run_length += 1
        else:
            if run_length > max_run_length:
                max_run_length = run_length
            run_length = 0
            
    if run_length > max_run_length:
        max_run_length = run_length
            
    print(max_run_length)
