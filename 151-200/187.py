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
limit = 10**8
isPrimeList = [True]*(limit//2 + 1)
iterlimit = int(limit**0.5)+1  # only check primes below this point
soe(limit // 2 + 1)  # create a sieve of Eratosthenes

# calculate prime list up to sqrt(limit)
primeList = []

for index, isPrime in enumerate(isPrimeList):
    if isPrime:
        primeList.append(index+2)
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
        if isPrimeList[i-2]:
            pi += 1

    # calculate semiprime partial sum
    semiprimes += (pi - ctr + 1)

    lowerLimit = upperLimit
    ctr -= 1

# print result
print("Number of semiprimes:", semiprimes)
