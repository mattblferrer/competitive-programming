from math import isqrt
from sympy.ntheory.residue_ntheory import nthroot_mod


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = isqrt(n) + 1
    isPrimeList = [True]*n

    # for 0 and 1 
    isPrimeList[0] = isPrimeList[1] = False

    # for 2 and 3
    for i in [2, 3]:
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            isPrimeList[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in [0, 2]: 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                isPrimeList[multiple] = False  

    return isPrimeList


# returns a list of numbers that do not have a primitive root
def primitive_root_sieve(n: int) -> list[int]:
    sieve = [False]*n
    is_prime_list = soe(n)
    prime_list = [i for i, isprime in enumerate(is_prime_list) if isprime]
    prime_list.remove(2)

    for i in {0, 1, 2, 4}:
        sieve[i] = True
    
    for p in prime_list:
        k = p
        while k < n:
            sieve[k] = True
            if 2*k < n:
                sieve[2*k] = True

            k *= p

    return [i for i, x in enumerate(sieve) if not x]


def main():
    # declare variables
    limit = 2 * 10**7
    sieve = primitive_root_sieve(limit + 1)
    sum_i = limit - len(sieve) - 2  # not counting 0, 1, 2 

    # check through all numbers with no primitive root
    x = 0
    for n in sieve:
        sum_i += nthroot_mod(1, 2, n, True)[-2]

        if n > x:  # progress tracker
            x += 10_000
            print(n, sum_i)

    # print result
    print(f"{sum_i}")


if __name__ == "__main__":
    main()
