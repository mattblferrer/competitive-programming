"""
If n, p is a valid solution, then n is always a cube k.
k^3+p is always equal to (k+1)^3. 
Therefore, we can look for prime solutions by checking numbers of the form
(k+1)^3 - k^3 for primality.

(k+1)^3 - k^3
k^3 + 3*k^2 + 3*k + 1 - k^3
= 3*k^2 + 3*k + 1
"""
from math import sqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = int(sqrt(n)) + 1
    isPrimeList = [True]*(n+1)

    # for 0 and 1 
    isPrimeList[0] = isPrimeList[1] = False

    # for 2 and 3
    for i in [2, 3]:
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            isPrimeList[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in [0, 2]: 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                isPrimeList[multiple] = False  

    return isPrimeList


# declare variables
limit = 1000000
numPrimes = 0
isPrimeList = soe(limit)  # create a sieve of Eratosthenes

# create set of primes
primeSet = {i for i, isPrime in enumerate(isPrimeList) if isPrime}

# calculate n for value of p
k, p = 1, 1

while p < limit:
    p = 3*k*k + 3*k + 1

    if p in primeSet:
        numPrimes += 1

    k += 1

# print result
print(numPrimes)
