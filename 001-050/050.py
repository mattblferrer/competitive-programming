from math import sqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = int(sqrt(n)) + 1
    isPrimeList = [True]*n

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
maximumLength = 0  # length of longest sum of consecutive primes

# create list of primes
isPrimeList = soe(limit)
primes = [idx for idx, isprime in enumerate(isPrimeList) if isprime]
currentIndex = 0
maximumPrime = 0

# main loop
length = len(primes)  # number of primes below 1 million

while currentIndex < (length - 1):  # iterate through all starting primes
    sumPrimes = primes[currentIndex]
    ctr = currentIndex
    
    # calculate sums of consecutive primes
    while sumPrimes < limit:
        ctr += 1
        sumPrimes += primes[ctr]

    sumPrimes -= primes[ctr]  # backtrack to find highest lower than limit

    # check if chain of primes is the longest
    if sumPrimes in primes and ctr - currentIndex > maximumLength:
        maximumLength = ctr - currentIndex 
        maximumPrime = sumPrimes
        print(currentIndex, maximumPrime, maximumLength) 

    # next prime
    currentIndex += 1

# print result
print(f"The prime below 1 million that can be written as the sum of the most\
consecutive primes is {maximumPrime}, length: {maximumLength}")
