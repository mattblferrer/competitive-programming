"""
SOURCE: https://rosettacode.org/wiki/Miller%E2%80%93Rabin_primality_test#Python
"""

from functools import cache
from math import lcm, sqrt


# test for composite
def _try_composite(a: int, d: int, n: int, s: int) -> bool:
    if pow(a, d, n) == 1:
        return False
    for i in range(s):
        if pow(a, 2**i * d, n) == n-1:
            return False
    return True  # n is definitely composite
 

# Miller-Rabin primality test
def is_prime_mr(n: int) -> bool:
    if n in _known_primes:
        return True
    if any((n % p) == 0 for p in _known_primes) or n in (0, 1):
        return False
    d, s = n - 1, 0
    while not d % 2:
        d, s = d >> 1, s + 1
    # Returns exact according to http://primes.utm.edu/prove/prove2_3.html
    if n < 1373653: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3))
    if n < 25326001: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5))
    if n < 118670087467: 
        if n == 3215031751: 
            return False
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7))
    if n < 2152302898747: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11))
    if n < 3474749660383: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13))
    if n < 341550071728321: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13, 17))
    else:
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13, 17, 19, 23))

_known_primes = [2, 3]


# returns the Pisano period mod n
def pisano_period(n: int) -> int:
    factors = prime_factorize(n)

    if len(factors) != 1:  # get LCM of Pisano periods of prime powers
        period = 1
        for factor in factors.items():
            # special cases for powers of 2 and 5
            if factor[0] == 2:
                period = lcm(period, 3 * 2**(factor[1] - 1))
            elif factor[0] == 5:
                period = lcm(period, 4 * 5**factor[1])
            else:
                period = lcm(period, pisano_period(factor[0]))
        
        return period

    # Pisano period for 1 factor
    a, b, ctr = 0, 1, 0
    while True:
        a, b = b, (a + b) % n  # calculate next term in Fibonacci mod n
        ctr += 1
        if a == 0 and b == 1:
            break

    return ctr


# returns the prime factors of num with multiplicity (repeating)
def prime_factorize(num: int) -> dict[int]:
    factors = {}

    for i in (2, 3):
        count = 0
        while num % i == 0:  # for only even prime
            count += 1
            num //= i
        if count:
            factors[i] = count

    for i in range(5, int(sqrt(num)) + 1, 6):  # for 6k +- 1
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


# generate next prime
def next_prime_mr(num: int) -> int:
    if num % 2 == 0:
        num -= 1

    while True:
        num += 2
        if is_prime_mr(num):
            return num


@cache
# returns the (n+1)'th Fibonacci number with modulo
def fibonacci_mod(n: int, mod: int) -> int:
    if n == 0:
        return 1
    elif n == 1:
        return 1
    return (fibonacci_mod((n + 1) // 2, mod) * fibonacci_mod(n // 2, mod) 
    + fibonacci_mod((n - 1) // 2, mod) * fibonacci_mod((n - 2) // 2, mod)) % mod


def main():
    # declare variables
    n_start = 10**14
    limit = 100_000
    mod = 1234567891011
    a_n = next_prime_mr(n_start)  # a(1)
    b_start_idx = a_n % pisano_period(mod)  # a(n) in the Pisano period
    sum_b = 0

    # calculate first b(n) and b(n-1) for start of Fibonacci sequence x, y
    x = fibonacci_mod(b_start_idx - 2, mod)
    y = fibonacci_mod(b_start_idx - 1, mod)

    # calculate next b(n)'s
    for _ in range(limit):
        sum_b += y
        prev_a_n = a_n
        a_n = next_prime_mr(a_n)
        a_n_diff = a_n - prev_a_n
        
        # get next b(n) in Fibonacci sequence by calculating next a(n)'s
        for _ in range(a_n_diff):  
            x, y = y, (x + y) % mod

    # print result
    print(f"The sum of b(n) from 1 to {limit} = {sum_b % mod}")


if __name__ == "__main__":
    main()
