"""
SOURCE: https://rosettacode.org/wiki/Miller%E2%80%93Rabin_primality_test#Python
"""
def _try_composite(a: int, d: int, n: int, s: int) -> bool:
    """returns True if a number n is definitely composite"""
    if pow(a, d, n) == 1:
        return False
    for i in range(s):
        if pow(a, 2**i * d, n) == n-1:
            return False
    return True  # n  is definitely composite
 

def is_prime_mr(n: int) -> bool:
    """returns True if a number n is likely prime using Miller-Rabin test"""
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
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 
        13))
    if n < 341550071728321: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 
        13, 17))
    else:
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 
        13, 17, 19, 23))

_known_primes = [2, 3]


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = int(n ** 0.5) + 1
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


def num_contains_substring(n: int, substring: str) -> bool:
    """returns True if number n contains the substring given"""
    n = str(n)  # convert number to string
    return substring in n


def is_primeproof(n: int) -> bool:
    """returns True if any digit of the number can't be changed to 
    make a prime"""
    n = str(n)  # convert number to list of characters
    for i, digit in enumerate(n):
        for j in range(1, 10):
            if j == digit:  # just equal to original number
                continue

            check = n[:i] + str(j) + n[i+1:]   
            if is_prime_mr(int(check)):
                return False
    return True


def main():
    # declare variables
    limit = 200
    limit_p = 200_000
    is_prime_list = soe(limit_p)  # guess limit
    prime_list = [i for i, is_prime in enumerate(is_prime_list) if is_prime]
    sqube_list = set()

    # loop through squbes for p == 2 and p == 5
    for p in (2, 5):
        for q in prime_list:
            if p == q:  # distinct primes needed
                continue

            sqube = p * p * q * q * q
            if num_contains_substring(sqube, '200') and is_primeproof(sqube):
                sqube_list.add(sqube)
                print(p, q, sqube) 

    # loop through squbes p^2*q^3 for p and q
    maximum = max(sqube_list) 
    for p in prime_list:
        for q in prime_list:
            if p == q:  # distinct primes needed
                continue

            sqube = p * p * q * q * q

            if sqube > maximum:
                break

            if num_contains_substring(sqube, '200') and is_primeproof(sqube):
                sqube_list.add(sqube)
                print(p, q, sqube)  

    answer = sorted(sqube_list)[limit - 1]  # get 200th element of sqube array

    # print result
    print(f"The {limit}th prime-proof sqube containing the contiguous sub"\
    f"string 200 is {answer}")


if __name__ == "__main__":
    main()
