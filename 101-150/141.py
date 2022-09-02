from time import time
ctime = time()


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
    for i in range(5, limit+2, 6):  
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


# returns the prime factors of num (non-repeating)
def prime_factorize(num):
    factors = set()

    for i in [2, 3]:
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        for j in [-1, 1]:
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)

    if num != 1:
        factors.add(num)

    return factors


# returns True if a number's square is progressive, False otherwise
def is_progressive(n):
    sqr = n*n
    factors = prime_factorize(n)
    iterlimit = int(n**(2/3))

    for fac in factors:
        for d in range(n - n % (fac*fac), iterlimit, -fac*fac):
            q, r = divmod(sqr, d)  # calculate remainder and quotient

            if r*q == d*d:  # check if geometric
                print(n, r, d, q, fac)  # print progressive n
                return True
    return False


# declare variables
limit = int((10**12)**0.5)
progressiveSum = 9  # include 9 as given

# create a sieve of Eratosthenes
isPrimeList = [True]*limit
soe(limit)

# iterate through values of i
for i in range(4, limit):
    if not isPrimeList[i]:
        if is_progressive(i):
            progressiveSum += i*i

# print result
print("The sum of all progressive perfect squares is:", progressiveSum)

ntime = time()
print(ctime - ntime)
