"""
This program is a bit slow, and could be optimized further.
(Took approximately 1 hour to run)
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
p1 = 5  # start at p1 = 5, p2 = 7
sSum = 0
isPrimeList = soe(limit + 100)  # create a sieve of Eratosthenes

# generate list of primes and iterate through it
for p2, isprime in enumerate(isPrimeList[7:], start=7):
    if p1 > limit:
        break

    if isprime:
        p10 = 10**(len(str(p1)))  # power of 10 to add to p1
        r = p1  # remainder when divided by p2
        r_p10 = p10 % p2  # remainder of power of 10 divided by p2

        # calculate value of S for p1, p2
        for i in range(1, p2):
            r += r_p10

            if r >= p2:  # keep mod p2 under p2
                r -= p2

            if r == 0:  # p1 divides p2
                s = i*p10 + p1  # append last digits of p1 to counter
                sSum += s
                print(p1, p2, s)  # print running p1, p2, s
                break

        p1 = p2

# print result
print(sSum)
