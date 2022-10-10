from math import isqrt


# determines if num is prime
def isprime(num: int) -> bool:
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# generate next prime
def next_prime(num: int) -> int:
    while True:
        num += 2
        if isprime(num):
            return num


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = isqrt(n) + 1
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


# finds the prime that solves the problem, given a starting number
def find_prime_51(n: int) -> int:
    # calculate all possible values in prime family
    while True:
        # create a sieve of Eratosthenes
        length = len(str(n))
        p10 = 10**length  # lowest power of 10 above n
        isPrimeList = soe(p10)

        # generate a set of primes
        primes = {i for i, prime in enumerate(isPrimeList) if prime}

        # generate all possible ways to replace digits in num
        perms = [format(n, f'0{length-1}b') for n in range(1, 2**(length-1))]
        
        while n < p10:
            strN = str(n)

            # try all combinations and check if it is part of an 8-prime family
            for perm in perms:
                pos = [i for i, d in enumerate(perm) if d == '1']
                validSubs = []  # array of valid digit substitutions in family
                for i in range(10):
                    temp = strN  # temporary variable for digit replacement
                    for j in pos:  # positions of digits to be replaced
                        temp = temp[:j] + str(i) + temp[j+1:]

                    # check if prime and has no leading zeroes
                    if int(temp) in primes and temp[0] != '0':
                        validSubs.append(temp)

                if len(validSubs) == 8:
                    strN = validSubs[0]
                    return strN

            n = next_prime(n) # move to next prime


# declare variables
n = 56993  # starting num

# print result
print(f"Prime: {find_prime_51(n)}")
