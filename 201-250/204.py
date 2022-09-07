from math import isqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = isqrt(n) + 1
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


# returns True if number is a generalized Hamming number
def is_gen_hamming(n: int) -> bool: 
    for prime in primeList:
        while n % prime == 0:
            n //= prime

        if n == 1:
            return True

    return False


# create a sieve of Eratosthenes
soe_limit = 100
isPrimeList = soe(soe_limit)

# convert to list of primes
primeList = [i for i in range(soe_limit) if isPrimeList[i]]

# declare variables
hammingNums = 0
limit = 10**9

# main loop
for i in range(1, limit + 1):
    if is_gen_hamming(i):
        hammingNums += 1

    # progress tracker
    if i % 1000000 == 0:
        print(i)

# print result
print(f"Number of generalized Hamming numbers: {hammingNums}")
