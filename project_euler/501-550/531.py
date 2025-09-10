from functools import cache
from sympy.ntheory.modular import crt


def prime_factorize(num: int) -> set[int]:
    """returns the prime factors of num (non-repeating)"""
    factors = set()

    for i in (2, 3):
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(5, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)

    if num != 1:
        factors.add(num)

    return factors


@cache
def totient(num: int) -> int:
    """returns the Euler's totient of the number num using Euler's 
    product formula"""
    p_factors = prime_factorize(num)
    phi = num  # totient
    for factor in p_factors:
        phi = phi*(factor-1)//factor

    return phi


def main():
    # declare variables
    lower_limit = 1_000_000
    upper_limit = 1_005_000
    sum_f = 0

    # loop through all n < m between lower and upper limits
    for n in range(lower_limit, upper_limit):
        for m in range(n + 1, upper_limit):
            solutions = crt([n, m], [totient(n), totient(m)])
            if solutions:
                sum_f += solutions[0]

        print(f"n: {n}")  # progress tracker

    # print result
    print(sum_f)


if __name__ == "__main__":
    main()
