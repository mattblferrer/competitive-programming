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
limit = 10**8
isPrimeList = [True]*(limit//2 + 1)
iterlimit = int(limit**0.5)+1  # only check primes below this point
soe(limit // 2 + 1)  # create a sieve of Eratosthenes

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
print("Number of semiprimes:", semiprimes)
