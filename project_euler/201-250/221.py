from itertools import product
from math import prod


def prime_factorize(num: int) -> dict[int]:
    """returns the prime factors of num with multiplicity (repeating)"""
    factors = {}

    for i in (2, 3):
        count = 0
        while num % i == 0:  # for only even prime
            count += 1
            num //= i
        if count:
            factors[i] = count

    for i in range(5, int(num ** 0.5) + 1, 6):  # for 6k +- 1
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


def factorize(num: int) -> list[int]:
    """returns the factors of num (non-repeating)"""
    factor_ctr = prime_factorize(num)
    powers = [
        [base**power for power in range(count+1)]
        for base, count in factor_ctr.items()
    ]
    factors = [prod(power_combo) for power_combo in product(*powers)]

    return factors


def main():
    # declare variables
    alexandrian_set = set()

    for i in range(1, 80_000):  # optimized limit
        for j in factorize(i ** 2 + 1):
            alexandrian = i * (i + j) * (i + (i ** 2 + 1) // j)
            alexandrian_set.add(alexandrian)

    # print result
    print(sorted(alexandrian_set)[149_999])


if __name__ == "__main__":
    main()
