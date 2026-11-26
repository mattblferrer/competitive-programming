# Contents
#   soe             Sieve of Eratosthenes: s[i] is truthy iff i is prime, for 0 <= i < n, O(n log log n)
#   primes_below    list of the primes < n, O(n log log n)
#   spf_sieve       smallest prime factor of every i < n (spf[0] = spf[1] = 0), O(n log log n)
#   is_prime        deterministic Miller-Rabin for n < 3.3e24, a strong probable-prime test above that
#   factorize       {prime: exponent} of n >= 1 (trial division, then Pollard's rho)
#   prime_factors   distinct prime factors of n >= 1, increasing
#   next_prime      smallest prime > n
#   prev_prime      largest prime < n, None if n <= 2
# isprime and prime_factorize are aliases of is_prime and factorize, for the old Project Euler helpers

from math import gcd, isqrt
from random import randrange


# Sieve of Eratosthenes: s[i] is 1 iff i is prime, for 0 <= i < n (a bytearray, so use it as a truth value);
# multiples of each prime p are cleared with one slice assignment starting at p^2, O(n log log n)
def soe(n: int) -> bytearray:
    s = bytearray([1]) * n
    s[:2] = b"\x00" * min(n, 2)
    for p in range(2, isqrt(max(n - 1, 0)) + 1):
        if s[p]:
            s[p * p::p] = bytes(len(range(p * p, n, p)))
    return s


# list of the primes < n, O(n log log n)
def primes_below(n: int) -> list[int]:
    return [i for i, b in enumerate(soe(n)) if b]


# smallest prime factor of every i < n, with spf[0] = spf[1] = 0; factorize x < n by dividing by spf[x] repeatedly;
# the primes up to sqrt(n) overwrite their multiples from largest to smallest, so the smallest one is left,
# O(n log log n)
def spf_sieve(n: int) -> list[int]:
    spf = list(range(n))
    spf[:2] = [0] * min(n, 2)
    for p in reversed(primes_below(isqrt(max(n - 1, 0)) + 1)):
        spf[p * p::p] = [p] * len(range(p * p, n, p))
    return spf


_SMALL = (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41)


# deterministic Miller-Rabin for n < 3.3e24 (the 13 prime bases up to 41 have no strong pseudoprime below that);
# above that it is a strong probable-prime test that no known composite passes, O(log^3 n)
def is_prime(n: int) -> bool:
    if n < 2:
        return False
    for p in _SMALL:
        if n % p == 0:
            return n == p
    d, s = n - 1, 0
    while d % 2 == 0:
        d, s = d // 2, s + 1
    for a in _SMALL:
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(s - 1):
            x = x * x % n
            if x == n - 1:
                break
        else:
            return False
    return True


# a nontrivial factor of a composite n (Pollard's rho, Brent's variant, gcd taken in batches), O(n^(1/4)) expected
def _pollard_rho(n: int) -> int:
    if n % 2 == 0:
        return 2
    while True:
        c, y, m = randrange(1, n), randrange(n), 128
        g, r, q = 1, 1, 1
        while g == 1:
            x = y
            for _ in range(r):
                y = (y * y + c) % n
            k = 0
            while k < r and g == 1:
                ys = y
                for _ in range(min(m, r - k)):
                    y = (y * y + c) % n
                    q = q * abs(x - y) % n
                g = gcd(q, n)
                k += m
            r *= 2
        if g == n:  # the batch overshot: step through it one at a time
            g = 1
            while g == 1:
                ys = (ys * ys + c) % n
                g = gcd(abs(x - ys), n)
        if g != n:
            return g


# {prime: exponent} of n >= 1, keys in increasing order: trial division by primes below 1000, then Pollard's rho
# on what is left; fast for any n up to ~1e30 unless it has two prime factors above ~1e12
def factorize(n: int) -> dict[int, int]:
    res = {}
    for p in _SMALL_PRIMES:
        if p * p > n:
            break
        while n % p == 0:
            res[p] = res.get(p, 0) + 1
            n //= p
    stack = [n] if n > 1 else []
    while stack:
        x = stack.pop()
        if is_prime(x):
            res[x] = res.get(x, 0) + 1
        else:
            d = _pollard_rho(x)
            stack += [d, x // d]
    return dict(sorted(res.items()))


_SMALL_PRIMES = primes_below(1000)


# distinct prime factors of n >= 1, increasing
def prime_factors(n: int) -> list[int]:
    return list(factorize(n))


# smallest prime > n, O(log n) Miller-Rabin tests on average
def next_prime(n: int) -> int:
    if n < 2:
        return 2
    n += 1 + n % 2  # next odd number above n
    while not is_prime(n):
        n += 2
    return n


# largest prime < n, None if n <= 2
def prev_prime(n: int) -> int | None:
    if n <= 2:
        return None
    if n == 3:
        return 2
    n -= 1 + n % 2  # previous odd number below n
    while not is_prime(n):
        n -= 2
    return n


isprime = is_prime
prime_factorize = factorize
