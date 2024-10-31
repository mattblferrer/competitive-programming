#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'solve' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts INTEGER_ARRAY a as parameter.
#

def solve(a):
    # get all divisors of the total number of people 
    sum_a = sum(a)
    divisors = [1, sum_a]
    for i in range(2, int(math.sqrt(sum_a)) + 1):
        if sum_a % i == 0:
            divisors.append(i)
            if i != sum_a // i:
                divisors.append(sum_a // i)
    
    # find if groups can fit in the bus
    valid_bus_sizes = set()
    for d in divisors:
        bus_total = 0

        for a_i in a:
            if bus_total < d:
                bus_total += a_i
            if bus_total == d:
                bus_total = 0
            if bus_total > d:
                break
        
        else:
            valid_bus_sizes.add(d)

    return sorted(list(valid_bus_sizes))

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    a_count = int(input().strip())

    a = list(map(int, input().rstrip().split()))

    result = solve(a)

    fptr.write(' '.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
