from math import isqrt


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


# returns True if number is a generalized Hamming number
def is_gen_hamming(n): 
    for prime in primeList:
        while n % prime == 0:
            n //= prime

        if n == 1:
            return True

    return False


# create a sieve of Eratosthenes
soe_limit = 100
iterlimit = isqrt(soe_limit) + 1
isPrimeList = [True]*(soe_limit)
soe(soe_limit)

# convert to list of primes
primeList = [i for i in range(soe_limit) if isPrimeList[i]]

# declare variables
hammingNums = 0
limit = 10**9

# main loop
for i in range(1, limit + 1):
    if is_gen_hamming(i):
        hammingNums += 1

    # progress tracker
    if i % 1000000 == 0:
        print(i)

# print result
print(f"Number of generalized Hamming numbers: {hammingNums}")
