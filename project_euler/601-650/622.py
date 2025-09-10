from itertools import product
from math import isqrt, prod


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

    for i in range(5, isqrt(num) + 1, 6):  # for 6k +- 1
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


# returns the factors of num (non-repeating)
def factorize(num: int) -> list[int]:
    factor_ctr = prime_factorize(num)
    powers = [
        [base**power for power in range(count+1)]
        for base, count in factor_ctr.items()
    ]
    factors = [prod(power_combo) for power_combo in product(*powers)]

    return factors


def main():
    # declare variables
    s = 60
    checked_values = set()

    # loop through all lower s values (factors of s) to check for duplicates
    for check in sorted(factorize(s))[:-1]:
        checked_values.update({f + 1 for f in factorize(2**check - 1)})

    # loop through all n where 2^s mod (n-1) = 1
    s_sum = sum(f + 1 for f in factorize(2**s - 1) if f + 1 not in 
        checked_values)

    # print result
    print(f"Sum of all values of n, s(n) = {s}: {s_sum}")


if __name__ == "__main__":
    main()
