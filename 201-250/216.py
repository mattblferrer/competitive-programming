"""
SOURCE: https://rosettacode.org/wiki/Miller%E2%80%93Rabin_primality_test#Python
"""


# test for composite
def _try_composite(a: int, d: int, n: int, s: int) -> bool:
    if pow(a, d, n) == 1:
        return False
    for i in range(s):
        if pow(a, 2**i * d, n) == n-1:
            return False
    return True  # n  is definitely composite
 

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


def main():
    # declare variables
    limit = 50_000_000
    primes = 1  # count 2 

    # test 2n^2 - 1 for primality
    for n in range(1, limit):
        if n % 100_000 == 0:  # progress tracker
            print(f"{n}, primes: {primes}")
        if n % 7 == 2 or n % 7 == 5:
            continue
        if is_prime_mr(2*n*n - 1):
            primes += 1

    # print result
    print(f"Numbers t(n) up to {limit} that are prime: {primes}")


if __name__ == "__main__":
    main()
