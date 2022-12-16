from functools import cache
from math import isqrt


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


def main():
    @cache
    def gen_hamming(n: int, limit: int) -> None: 
        """adds Generalized Hamming numbers below limit to list using a
        recursive algorithm"""
        for prime in prime_list:
            if n * prime > limit: 
                return None
            gen_hammings.add(n * prime)
            gen_hamming(n * prime, limit)


    # create a sieve of Eratosthenes
    soe_limit = 100
    is_prime_list = soe(soe_limit + 1)
    prime_list = [i for i, isprime in enumerate(is_prime_list) if isprime]
    gen_hammings = {1}

    # declare variables
    limit = 10**9
    gen_hamming(1, limit)  # main loop

    # print result
    print(f"Number of generalized Hamming numbers: {len(gen_hammings)}")


if __name__ == "__main__":
    main()
