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
    # create a list of primes up to limit
    limit = 100_000_000
    is_prime_list = soe(limit)
    factorization = {i: 0 for i, isprime in enumerate(is_prime_list) if isprime}
    s_n = 1
    mod = 1_000_000_009

    # get prime factorization of factorial using Legendre's formula
    for p in factorization:
        p_power = p

        while p_power <= limit:
            factorization[p] += limit // p_power
            p_power *= p

    # calculate square of sum of unitary divisors
    for p, k in factorization.items():
        s_n = s_n * (pow(p, k * 2, mod) + 1) % mod

    # print result
    print(s_n)


if __name__ == "__main__":
    main()
