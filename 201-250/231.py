from math import log, sqrt


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
limit = 20000000
lLimit = 15000000  # lower limit
isPrimeList = soe(limit + 1)  # create a sieve of Eratosthenes
factorSum = 0

# calculate factors of factorials
diff = limit - lLimit
for index, isPrime in enumerate(isPrimeList):
    if isPrime:
        for power in range(1, int(log(limit, index))+1):
            factorSum += index*(limit // (index**power))  # get factors of n!
        for power in range(1, int(log(lLimit, index))+1):
            factorSum -= index*(lLimit // (index**power))  # get factors of r!  
        for power in range(1, int(log(diff, index))+1):
            factorSum -= index*(diff // (index**power))  # get factors of (n-r)!

# print result
print("Sum of terms in prime factorization:", factorSum)
