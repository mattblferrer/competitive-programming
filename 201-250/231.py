from math import log, sqrt


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
limit = 20000000
lLimit = 15000000 # lower limit
iterlimit = int(sqrt(limit)) + 1
isPrimeList = [True]*(limit + 1)
soe(limit + 1)  # create a sieve of Eratosthenes
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
