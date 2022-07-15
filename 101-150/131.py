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
def soe(n):
    # for even numbers
    multiple = 4

    while multiple < n:
        # assign multiples of 2 as not being prime
            isPrimeList[multiple - 2] = False  
            multiple += 2

    # for odd numbers
    for i in range(3, iterlimit, 2):  
        multiple = i ** 2  # initialize to i^2 for optimization

        while multiple < n:
            # assign multiples of i as not being prime
            isPrimeList[multiple - 2] = False  
            multiple += i


# declare variables
limit = 1000000
iterlimit = int(sqrt(limit)) + 1
isPrimeList = [True]*(limit + 1)
soe(limit)  # create a sieve of Eratosthenes

numPrimes = 0

# create set of primes
primeSet = set()

for index, isPrime in enumerate(isPrimeList):
    if isPrime:
        primeSet.add(index+2)

# calculate n for value of p
k = 1

while True:
    p = 3*k*k + 3*k + 1

    if p > limit:
        break
    elif p in primeSet:
        numPrimes += 1

    k += 1

# print result
print(numPrimes)
