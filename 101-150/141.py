# numba was used to speedup this code.
from numba import njit


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


@njit  # remove if numba is not installed
# returns True if a number's square is progressive, False otherwise
def is_progressive(n: int) -> bool:
    # returns the prime factors of num (non-repeating)
    def prime_factorize(num: int) -> set:
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
isPrimeList = soe(limit)

# iterate through values of i
for i in range(4, limit):
    if not isPrimeList[i]:
        if is_progressive(i):
            progressiveSum += i*i

# print result
print(f"The sum of all progressive perfect squares is: {progressiveSum}")
