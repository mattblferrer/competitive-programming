from functools import lru_cache
from math import isqrt, log2


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


@lru_cache(maxsize=2**20)
def prime_factorize_241(num: int, limit: int) -> dict[int]:
    """returns the prime factors of num with multiplicity (repeating) using
    trial division with numbers below limit"""
    factors = {}

    for i in (2, 3):
        count = 0
        while num % i == 0:  # for only even prime
            count += 1
            num //= i
        if count:
            factors[i] = count

    for i in range(5, limit + 1, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):
            count = 0
            while num % (i+j) == 0:
                count += 1
                num //= (i+j)
            if count:
                factors[i+j] = count

    if num != 1:
        factors[num] = 1

    return factors


@lru_cache(maxsize=2**20)
def sum_factors(num: int) -> int:
    """returns the sum of the factors of num, including num itself"""
    factor_sum = 1

    for i in (2, 3):  # for 2 and 3
        power = i
        c_factor = 1

        while num % i == 0:
            c_factor += power
            num //= i
            power *= i

        factor_sum *= c_factor

    for i in range(5, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):  # 6k +- 1
            power = (i + j)
            c_factor = 1
            while num % (i + j) == 0:
                c_factor += power
                num //= (i + j)
                power *= (i + j)

            factor_sum *= c_factor

    if num != 1:
        factor_sum *= num + 1

    return factor_sum


def main():
    @lru_cache(maxsize=2**20)
    def check_perfection_quotient(n: int) -> bool:
        """returns True if perfection quotient of n = k + 1/2 where k is an
        integer, and False otherwise"""
        sigma = sum_factors(n)

        # check perfection quotient
        if 2 * sigma % n == 0:  # check if denominator = 2
            if (2 * sigma // n) % 2 == 1:  # check odd numerator
                print(n, sigma)
                return True
        return False


    def multiply_factors_241(n: int, limit: int) \
        -> None:
        """recursively generate numbers below limit with prime factors from a
        list of primes"""
        if n in nums:
            return None
        if check_perfection_quotient(n):
            perfection_nums.add(n)
        nums.add(n)
        factors = prime_factorize_241(sum_factors(n), 500)

        for p in factors:
            if n * p <= limit and p < 500 and n * p not in nums: 
                # add factors to factor list for n
                multiply_factors_241(n * p, limit)

        return None


    # sieve out needed primes (estimate)
    nums = set()
    perfection_nums = set()
    limit = 10**18
    
    for i in range(1, int(log2(limit)) + 1):
        multiply_factors_241(2**i, limit)

    # print result
    print(sorted(perfection_nums))
    print(sum(perfection_nums))


if __name__ == "__main__":
    main()
