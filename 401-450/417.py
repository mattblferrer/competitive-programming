from itertools import product
from functools import lru_cache
from math import gcd, prod, isqrt


@lru_cache(maxsize=1048576)
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


# returns the Euler's totient of the number num using Euler's product formula
def totient(num: int, p_factors: list[int]) -> int:
    phi = num  # totient
    for factor in p_factors:
        phi = phi*(factor-1)//factor

    return phi


# returns the least common multiple of an array of numbers
def lcm_arr(arr: list[int]) -> int:
    lcm = 1
    for i in arr:
        lcm = lcm * i // gcd(lcm, i)
    return lcm


# divides out all factors of 2 and 5
def div_2_5(n: int) -> bool:
    for i in (2, 5):
        while n % i == 0:
            n //= i
            if n == 1:
                break

    return n


# returns the factors of num (non-repeating)
def factorize(num: int) -> list[int]:
    factor_ctr = prime_factorize(num)
    powers = [
        [base**power for power in range(count+1)]
        for base, count in factor_ctr.items()
    ]
    factors = [prod(power_combo) for power_combo in product(*powers)]

    return factors


@lru_cache(maxsize=1048576)
# returns the Carmichael function or reduced totient function of num
def carmichael(num: int) -> int:
    factor_ctr = prime_factorize(num)

    # if prime power
    if len(factor_ctr) == 1:  
        for base, power in factor_ctr.items():
            if base == 2 and power > 2:
                return totient(num, list(factor_ctr)) // 2
            else:
                return totient(num, list(factor_ctr))

    # if not prime power
    l_lambdas = [carmichael(base**power) for base, power in factor_ctr.items()]
        
    return lcm_arr(l_lambdas)


@lru_cache(maxsize=1048576)
# get length of recurring cycle of decimal fraction
def recurring_cycle(n: int) -> int:
    if n == 1:  # if terminates
        return 0

    for k in sorted(factorize(carmichael(n))):
        if pow(10, k, n) == 1:
            return k


def main():
    # declare variables
    limit = 100_000_000
    l_sum = 0

    # loop through all n up to limit
    for n in range(3, limit+1):
        l_sum += recurring_cycle(div_2_5(n))
        if n % 100_000 == 0:  # progress tracker
            print(n)

    # print result
    print(f"Sum of all L(n) up to {limit}: {l_sum}")


if __name__ == "__main__":
    # code for profiling
    import cProfile
    import pstats

    with cProfile.Profile() as pr:
        main() # code

    stats = pstats.Stats(pr)
    stats.sort_stats(pstats.SortKey.TIME)
    stats.print_stats()
