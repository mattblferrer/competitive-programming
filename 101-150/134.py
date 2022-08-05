"""
This program is a bit slow, and could be optimized further.
(Took approximately 1 hour to run)
"""
from math import sqrt


# creates a Sieve of Eratosthenes array of size n (offset)
def soe(n):
    # for even numbers
    multiple = 4

    while multiple < n:
        # assign multiples of 2 as not being prime
            isPrimeList[multiple - 2] = False  
            multiple += 2

    # for 3
    multiple = 9
    
    while multiple < n:
        # assign multiples of 3 as not being prime
            isPrimeList[multiple - 2] = False  
            multiple += 3

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6):  
        multiple = i*i  # initialize to i^2 for optimization

        while multiple < n:
            # assign multiples of i as not being prime
            isPrimeList[multiple - 2] = False  
            multiple += i

        multiple = (i+2)*(i+2)  # initialize to i^2 for optimization

        while multiple < n:
            # assign multiples of i as not being prime
            isPrimeList[multiple - 2] = False  
            multiple += (i+2)


# declare variables
limit = 1000000
iterlimit = int(sqrt(limit)) + 11
isPrimeList = [True]*(limit + 100)
soe(limit + 100)  # create a sieve of Eratosthenes

p1 = 5  # start at p1 = 5, p2 = 7
sSum = 0

# generate list of primes and iterate through it
for i, isprime in enumerate(isPrimeList[5:]):
    if p1 > limit:
        break

    if isprime:
        n = p1
        p2 = i + 7
        x = 10**(len(str(p1)))  # power of 10 to add to p1

        # calculate value of S for p1, p2
        while True:
            n += x

            if n % p2 == 0:
                sSum += n
                # print running p1, p2, and S
                print(p1, p2, n)
                break

        p1 = p2

# print result
print(sSum)
