from math import isqrt
from sympy.ntheory.modular import crt


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = isqrt(n) + 1
    is_prime_list = [True]*n

    # for 0 and 1 
    is_prime_list[0] = is_prime_list[1] = False

    # for 2 and 3
    for i in [2, 3]:
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            is_prime_list[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in [0, 2]: 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                is_prime_list[multiple] = False  

    return is_prime_list


def prime_power_sieve(n: int) -> list[int]:
    """returns a list of prime powers below n"""
    sieve = [False]*n
    is_prime_list = soe(n)
    prime_list = [i for i, isprime in enumerate(is_prime_list) if isprime]
    
    for p in prime_list:
        k = p
        while k < n:
            sieve[k] = True
            k *= p

    return [i for i, x in enumerate(sieve) if not x]
        

def main():
    # declare variables
    limit = 10000
    sieve = prime_power_sieve(limit + 1)
    sum_i = limit - len(sieve)

    x = 0
    for n in sieve:
        roots = []
        prime_powers = []

        # TODO Chinese Remainder Theorem for combining prime powers of n
        if n > x:  # progress tracker
            x += 10_000
            print(n, sum_i)

    # print result
    print(f"{sum_i}")


if __name__ == "__main__":
    main()
