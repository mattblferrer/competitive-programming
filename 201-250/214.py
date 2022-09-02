from math import sqrt


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


# returns the Euler's totient of the number num using Euler's product formula
def totient(num):
    p_factors = prime_factorize(num)
    phi = num  # totient
    for factor in p_factors:
        phi = phi * (factor-1)//factor

    return phi


# declare variables
limit = 40000000
iterlimit = int(sqrt(limit)) + 1
primeSum = 0
isPrimeList = [True]*(limit + 1)
chainLenList = [0]*(limit + 1)
soe(limit)  # create a sieve of Eratosthenes

# main loop
for i in range(1, limit):
    if isPrimeList[i]:
        n = i  # chain variable
        length = 1  # chain length

        while n > 1:
            # calculate totient
            if isPrimeList[n]:
                n -= 1
            else:
                n = totient(n)

            # check chain length list for already calculated chains
            if chainLenList[n]:
                length += chainLenList[n]
                break
            length += 1

        if length == 25:  # check chain length
            primeSum += i

        chainLenList[i] = length
    
    # progress tracker
    if i % 100000 == 0:
        print(i)

# print result
print("The sum of all primes < 40,000,000 with chain length 25:", primeSum)
