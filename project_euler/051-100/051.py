from math import isqrt


def isprime(num: int) -> bool:
    """returns True if num is prime"""
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


def next_prime(num: int) -> int:
    """return the smallest prime larger than num"""
    while True:
        num += 2
        if isprime(num):
            return num


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = isqrt(n) + 1
    is_prime_list = [True]*n

    # for 0 and 1 
    is_prime_list[0] = is_prime_list[1] = False

    # for 2 and 3
    for i in (2, 3):
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            is_prime_list[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in (0, 2): 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                is_prime_list[multiple] = False  

    return is_prime_list


def find_prime_51(n: int) -> int:
    """finds the prime that solves the problem, given a starting number n"""
    # calculate all possible values in prime family
    while True:
        # create a sieve of Eratosthenes
        length = len(str(n))
        p10 = 10**length  # lowest power of 10 above n
        is_prime_list = soe(p10)

        # generate a set of primes
        primes = {i for i, prime in enumerate(is_prime_list) if prime}

        # generate all possible ways to replace digits in num
        perms = [format(n, f'0{length-1}b') for n in range(1, 2**(length-1))]
        
        while n < p10:
            str_n = str(n)

            # try all combinations and check if it is part of an 8-prime family
            for perm in perms:
                pos = [i for i, d in enumerate(perm) if d == '1']
                valid_subs = []  # array of valid digit substitutions in family
                for i in range(10):
                    temp = str_n  # temporary variable for digit replacement
                    for j in pos:  # positions of digits to be replaced
                        temp = temp[:j] + str(i) + temp[j+1:]

                    # check if prime and has no leading zeroes
                    if int(temp) in primes and temp[0] != '0':
                        valid_subs.append(temp)

                if len(valid_subs) == 8:
                    str_n = valid_subs[0]
                    return str_n

            n = next_prime(n) # move to next prime


# declare variables
n = 56993  # starting num

# print result
print(f"Prime: {find_prime_51(n)}")
