from functools import cache
from math import sqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = int(sqrt(n)) + 1
    isPrimeList = [True]*(n+1)

    # for 0 and 1 
    isPrimeList[0] = isPrimeList[1] = False

    # for 2 and 3
    for i in (2, 3):
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            isPrimeList[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in (0, 2): 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                isPrimeList[multiple] = False  

    return isPrimeList


# returns the prime factors of num (non-repeating)
def prime_factorize(num: int) -> set:
    factors = set()

    for i in (2, 3):
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(5, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        for j in (0, 2):
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)

    if num != 1:
        factors.add(num)

    return factors


@cache
# returns the Euler's totient of the number num using Euler's product formula
def totient(num: int) -> int:
    p_factors = prime_factorize(num)
    phi = num  # totient
    for factor in p_factors:
        phi = phi*(factor-1)//factor

    return phi


# declare variables
limit = 40000000
prime_sum = 0
chainLenList = [0]*(limit + 1)
isPrimeList = soe(limit)  # create a sieve of Eratosthenes

# main loop
for i in range(1, limit):
    if isPrimeList[i]:
        n = i  # chain variable
        length = 1  # chain length

        while n > 1:
            # calculate totient
            n = n-1 if isPrimeList[n] else totient(n)

            # check chain length list for already calculated chains
            if chainLenList[n]:
                length += chainLenList[n]
                break
            length += 1

        if length == 25:  # check chain length
            prime_sum += i

        chainLenList[i] = length
    
    # progress tracker
    if i % 100000 == 0:
        print(i)

# print result
print(f"The sum of all primes < 40,000,000 with chain length 25: {prime_sum}")
