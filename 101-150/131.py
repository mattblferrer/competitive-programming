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
    # for 0 and 1
    isPrimeList[0] = False
    isPrimeList[1] = False

    # for even numbers
    multiple = 4

    while multiple < n:
        # assign multiples of 2 as not being prime
            isPrimeList[multiple] = False  
            multiple += 2

    # for 3
    multiple = 9
    
    while multiple < n:
        # assign multiples of 3 as not being prime
            isPrimeList[multiple] = False  
            multiple += 3

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6):  
        multiple = i*i  # initialize to i^2 for optimization

        while multiple < n:
            # assign multiples of i as not being prime
            isPrimeList[multiple] = False  
            multiple += i

        multiple = (i+2)*(i+2)  # initialize to i^2 for optimization

        while multiple < n:
            # assign multiples of i as not being prime
            isPrimeList[multiple] = False  
            multiple += (i+2)


# declare variables
limit = 1000000
numPrimes = 0
iterlimit = int(sqrt(limit)) + 1
isPrimeList = [True]*(limit + 1)
soe(limit)  # create a sieve of Eratosthenes

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
