from math import log2, sqrt


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


# create a sieve of Eratosthenes
limit = 100000
isPrimeList = soe(limit)

# declare variables
nonPrimeSum = 0
primeSet = set()

# main loop
for i in range(limit):
    if isPrimeList[i]:
        isFactor = False

        for j in range(int(log2(i))+1): 
            if pow(10, 10**j, i) == 1:  # check for prime factors of repunits
                isFactor = True
                primeSet.add(i)
                break

        if not isFactor or i == 3:
            nonPrimeSum += i

# print result
print(f"Sum of all the primes that will never be a factor: {nonPrimeSum}")
