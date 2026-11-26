# Contents
#   totient         Euler's totient phi(n); uses factorize
#   totient_sieve   phi(i) for every i < n, O(n log log n)
#   mobius          Mobius function mu(n); uses factorize
#   mobius_sieve    mu(i) for every i < n, O(n log log n)
#   divisors        sorted divisors of n >= 1; uses factorize
#   sigma           sum of d^k over the divisors d of n (k = 0 counts them); uses factorize
#   divisor_sieve   sum of d^k over the divisors of every i < n, O(n log n)
#   ext_gcd         (g, x, y) with a x + b y = g = gcd(a, b), O(log)
#   mod_inv         inverse of a mod m, None if gcd(a, m) != 1, O(log m)
#   crt             x with x = r[i] (mod m[i]) for all i, moduli need not be coprime: (x, lcm) or None
#   carmichael      Carmichael function lambda(n), the largest multiplicative order mod n; uses factorize
#   mult_order      multiplicative order of a mod n, None if gcd(a, n) != 1; uses carmichael, factorize
# mod_mult_inv(num, x) is an alias of mod_inv, for the old Project Euler helper

from math import gcd, isqrt, lcm, prod

from primes import factorize, primes_below


# Euler's totient phi(n) for n >= 1: n times the product of (1 - 1/p) over its primes; uses factorize
def totient(n: int) -> int:
    for p in factorize(n):
        n = n // p * (p - 1)
    return n


# phi(i) for every i < n: each prime p takes away 1/p of every multiple, one slice at a time, O(n log log n)
def totient_sieve(n: int) -> list[int]:
    phi = list(range(n))
    for p in primes_below(n):
        phi[p::p] = [x - x // p for x in phi[p::p]]
    return phi


# Mobius function mu(n) for n >= 1: 0 if a square divides n, else (-1)^(number of primes); uses factorize
def mobius(n: int) -> int:
    f = factorize(n)
    return 0 if any(e > 1 for e in f.values()) else (-1) ** len(f)


# mu(i) for every i < n (mu[0] = 0): each prime p flips the sign of its multiples and zeroes those of p^2,
# O(n log log n)
def mobius_sieve(n: int) -> list[int]:
    mu = [1] * n
    mu[:1] = [0] * min(n, 1)
    for p in primes_below(n):
        mu[p::p] = [-x for x in mu[p::p]]
        mu[p * p::p * p] = [0] * len(range(p * p, n, p * p))
    return mu


# sorted divisors of n >= 1, built prime by prime from factorize, O(number of divisors * log)
def divisors(n: int) -> list[int]:
    divs = [1]
    for p, e in factorize(n).items():
        divs = [d * p ** i for d in divs for i in range(e + 1)]
    return sorted(divs)


# sum of d^k over the divisors d of n >= 1 (k = 0: number of divisors, k = 1: sum of divisors); uses factorize
def sigma(n: int, k: int = 1) -> int:
    if k == 0:
        return prod(e + 1 for e in factorize(n).values())
    return prod((p ** (k * (e + 1)) - 1) // (p ** k - 1) for p, e in factorize(n).items())


# sum of d^k over the divisors d of every i < n (s[0] = 0), O(n log n)
def divisor_sieve(n: int, k: int = 1) -> list[int]:
    s = [0] * n
    for d in range(1, n):
        dk = d ** k
        s[d::d] = [x + dk for x in s[d::d]]
    return s


# (g, x, y) with a x + b y = g = gcd(a, b), O(log)
def ext_gcd(a: int, b: int) -> tuple[int, int, int]:
    x0, y0, x1, y1 = 1, 0, 0, 1
    while b:
        q = a // b
        a, b = b, a - q * b
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1
    return a, x0, y0


# inverse of a mod m in [0, m), None if gcd(a, m) != 1, O(log m)
def mod_inv(a: int, m: int) -> int | None:
    g, x, _ = ext_gcd(a % m, m)
    return x % m if g == 1 else None


# x with x = r[i] (mod m[i]) for every i, the moduli need not be coprime: (x, M) with 0 <= x < M = lcm(m),
# meaning every solution is x mod M, or None if the congruences contradict each other, O(k log)
def crt(r: list[int], m: list[int]) -> tuple[int, int] | None:
    x, M = 0, 1
    for ri, mi in zip(r, m):
        g, p, _ = ext_gcd(M, mi)  # p M = g (mod mi)
        if (ri - x) % g:
            return None
        x += (ri - x) // g * p % (mi // g) * M
        M = M // g * mi
        x %= M
    return x, M


# Carmichael function lambda(n): lambda(p^k) = phi(p^k), except lambda(2^k) = 2^(k - 2) for k >= 3, and the lcm over
# the prime powers of n; uses factorize
def carmichael(n: int) -> int:
    res = 1
    for p, e in factorize(n).items():
        res = lcm(res, 2 ** (e - 2) if p == 2 and e >= 3 else p ** (e - 1) * (p - 1))
    return res


# multiplicative order of a mod n: the smallest k > 0 with a^k = 1 (mod n), None if gcd(a, n) != 1; k divides
# lambda(n), so strip each prime factor of lambda(n) while a^(k / q) stays 1; uses carmichael, factorize
def mult_order(a: int, n: int) -> int | None:
    if gcd(a, n) != 1:
        return None
    k = carmichael(n)
    for q in factorize(k):
        while k % q == 0 and pow(a, k // q, n) == 1 % n:
            k //= q
    return k


mod_mult_inv = mod_inv
