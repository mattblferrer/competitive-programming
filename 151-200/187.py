# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = int(n**0.5) + 1
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
limit = 10**8
iterlimit = int(limit**0.5)+1  # only check primes below this point
isPrimeList = soe(limit // 2 + 1)  # create a sieve of Eratosthenes

# calculate prime list up to sqrt(limit)
primeList = []

for index, isPrime in enumerate(isPrimeList):
    if isPrime:
        primeList.append(index)
    if index > iterlimit:
        break

# calculate semiprimes
ctr = len(primeList)
semiprimes = 0
pi = 0  # current prime counting function
lowerLimit = 2

for prime in reversed(primeList):
    upperLimit = limit // prime + 1

    # count primes below limit / prime
    for i in range(lowerLimit, upperLimit):
        if isPrimeList[i]:
            pi += 1

    # calculate semiprime partial sum
    semiprimes += (pi - ctr + 1)

    lowerLimit = upperLimit
    ctr -= 1

# print result
print(f"Number of semiprimes: {semiprimes}")
