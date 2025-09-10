"""
SOURCE: https://rosettacode.org/wiki/Miller%E2%80%93Rabin_primality_test#Python
"""
# test for composite
def _try_composite(a: int, d: int, n: int, s: int) -> bool:
    if pow(a, d, n) == 1:
        return False
    for i in range(s):
        if pow(a, 2**i * d, n) == n-1:
            return False
    return True  # n  is definitely composite
 

# Miller-Rabin primality test
def is_prime_mr(n: int) -> bool:
    if n in _known_primes:
        return True
    if any((n % p) == 0 for p in _known_primes) or n in (0, 1):
        return False
    d, s = n - 1, 0
    while not d % 2:
        d, s = d >> 1, s + 1
    # Returns exact according to http://primes.utm.edu/prove/prove2_3.html
    if n < 1373653: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3))
    if n < 25326001: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5))
    if n < 118670087467: 
        if n == 3215031751: 
            return False
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7))
    if n < 2152302898747: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11))
    if n < 3474749660383: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13))
    if n < 341550071728321: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13, 17))
    else:
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13, 17, 19, 23))

_known_primes = [2, 3]

# declare variables
limit = 150000000
sumN = 0

# check primality
for i in range(10, limit, 10):
    # check factors of i
    if any(i % j == 0 for j in {3, 7, 13}):
        continue

    # check for primality
    sqr = i*i
    if all(is_prime_mr(sqr+j) for j in {1, 3, 7, 9, 13, 27}):
        # check if primes found are consecutive
        if not any(is_prime_mr(sqr+j) for j in {11, 17, 19, 21, 23}): 
            print(i)
            sumN += i

# print result
print("sum of all such integers n:", sumN)
