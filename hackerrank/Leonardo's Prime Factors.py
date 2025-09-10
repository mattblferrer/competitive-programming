#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'primeCount' function below.
#
# The function is expected to return an INTEGER.
# The function accepts LONG_INTEGER n as parameter.
#

def primeCount(n):
    def isPrime(n): 
        for i in range(2, int(math.sqrt(n)) + 1):
            if n % i == 0:
                return False
        return n > 1
        
    def nextPrime(n):
        while True:
            n += 1
            if isPrime(n):
                return n
    
    # generate list of products of primes up to limit
    limit = 10 ** 18
    prime_product = 1
    curr_prime = 2
    prime_products = []
    
    while prime_product <= limit:
        prime_product *= curr_prime
        prime_products.append(prime_product)
        curr_prime = nextPrime(curr_prime)
        
    # find smallest i where product of first i primes greater than n
    for i, prime_product in enumerate(prime_products):
        if prime_product > n:
            return i

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        n = int(input().strip())

        result = primeCount(n)

        fptr.write(str(result) + '\n')

    fptr.close()
