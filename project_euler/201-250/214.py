from functools import cache
from math import sqrt


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = int(sqrt(n)) + 1
    is_prime_list = [True]*(n + 1)

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


def prime_factorize(num: int) -> set:
    """returns the prime factors of num (non-repeating)"""
    factors = set()

    for i in (2, 3):
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(5, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)

    if num != 1:
        factors.add(num)

    return factors


@cache
def totient(num: int) -> int:
    """returns the Euler's totient of the number num using Euler's 
    product formula"""
    p_factors = prime_factorize(num)
    phi = num  # totient
    for factor in p_factors:
        phi = phi*(factor-1)//factor

    return phi


def main():
    # declare variables
    limit = 40_000_000
    prime_sum = 0
    chain_len_list = [0]*(limit + 1)
    is_prime_list = soe(limit)  # create a sieve of Eratosthenes

    # main loop
    for i, is_prime in enumerate(is_prime_list):
        if is_prime:
            n = i  # chain variable
            length = 1  # chain length

            while n > 1:
                # calculate totient
                n = n - 1 if is_prime_list[n] else totient(n)

                # check chain length list for already calculated chains
                if chain_len_list[n]:
                    length += chain_len_list[n]
                    break
                length += 1

            if length == 25:  # check chain length
                prime_sum += i

            chain_len_list[i] = length
        
        # progress tracker
        if i % 100_000 == 0:
            print(i)

    # print result
    print(f"The sum of all primes < {limit} with chain length 25: {prime_sum}")


if __name__ == "__main__":
    main()
