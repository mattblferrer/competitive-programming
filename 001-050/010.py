from math import sqrt


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = int(sqrt(n)) + 1
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


# declare variables
limit = 2_000_000
isPrimeList = soe(limit)

# sum up all primes found by sieve
sum_primes = sum(idx for idx, isPrime in enumerate(isPrimeList) if isPrime)

# print result
print(sum_primes)
