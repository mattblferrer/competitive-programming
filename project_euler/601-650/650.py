from math import sqrt
from numba import njit
import numpy as np


def main():
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


    @njit
    def prime_factorize_650(num: int) -> np.array:
        """returns the prime factors of num with multiplicity (repeating) as a
        numpy array"""
        factors = [0]*length
        ctr = 0

        for p in prime_list:
            if p > num: 
                break

            while num % p == 0:
                factors[ctr] += 1
                num //= p

            ctr += 1

        return np.array(factors)


    @njit
    def mod_mult_inv(num: int, x: int) -> int:
        """returns the modular multiplicative inverse of num mod x"""
        r0, r1 = x, num
        t0, t1 = 0, 1

        # extended Euclidean algorithm
        while r1 != 0:
            q = r0 // r1
            r0, r1 = r1, r0 % r1  # remainders after Euclidean division
            t0, t1 = t1, (t0 - t1*q) % x
            
        return t0


    def sum_factors_650(factors: np.array, n: int) -> int:
        """returns the sum of the factors of num mod n given its prime 
        factorization"""
        sum_factors = 1
        for p, power in zip(prime_list, factors):
            # convert from numpy type to int type for arbitrary precision
            p, power = int(p), int(power)

            if power:
                sum_factors = (sum_factors * (pow(p, power + 1, n) - 1) 
                * int(mmi_list[p])) % n
        
        return sum_factors


    @njit
    def comb_factor_array(n: int) -> np.array:
        """returns the factorization of the product of all combinations of 
        two numbers n choose k"""
        factors = np.array([0]*length)
        for k in range(1, n + 1):
            factors += factor_list[k] * (2*k - 1 - n)

        return factors


    # declare variables
    n_limit = 20_000
    mod = 1_000_000_007
    s = 0
    is_prime_list = soe(n_limit + 1)
    prime_list = np.array([i for i, is_prime in enumerate(is_prime_list) 
    if is_prime])  # convert to numpy array for speedup
    length = len(prime_list)

    # store factorizations of n up to limit
    factor_list = np.array([prime_factorize_650(n) for
    n in range(n_limit + 1)])

    # store modular multiplcative inverses of primes up to limit
    mmi_list = np.array([mod_mult_inv(n - 1, mod) for n in range(n_limit + 1)])

    # calculate S(n)
    for n in range(1, n_limit + 1):
        factors = comb_factor_array(n)  # B(n)
        d = sum_factors_650(factors, mod)  # D(n)
        s = (s + d) % mod  # add D(n) to previous S(n)
        
        if n % 1_000 == 0:  # progress tracker
            print(f"n = {n}, s = {s}")

    # print result
    print(f"S({n}) = {s}")


if __name__ == "__main__":
    main()
