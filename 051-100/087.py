from math import sqrt


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
limit = 5*10**7  # 50 million
isPrimeList = soe(int(sqrt(limit)) + 1)
expressibleNumbers = set()
a = 0

# create list of primes
primeList = [i for i, isp in enumerate(isPrimeList) if isp]

# calculate root
limit_4 = int(limit**(1/4)) + 1

# iterate through all a, b, c for which a^4 + b^3 + c^2 < limit
while primeList[a] < limit_4:
    # calculate root, reset b
    limit_3 = int((limit - a**4)**(1/3)) + 1
    b = 0

    while primeList[b] < limit_3:
        # calculate root, reset c
        limit_2 = int((limit - a**3)**(1/2)) + 1
        c = 0

        while primeList[c] < limit_2:
            # calculate sum and compare against existing set
            n = primeList[a]**4 + primeList[b]**3 + primeList[c]**2

            if n < limit:
                expressibleNumbers.add(n)
            c += 1
        b += 1
    a += 1

# print result
print(len(expressibleNumbers))
