from functools import cache
from math import isqrt, lcm


# returns a list of all the possible divisors d of n, n % 4 == 2, d < sqrt(n)
# as a list with a starting index of n, from x to y where d + n / d 
# could be prime
def generate_divisor_list_357(x: int, y: int) -> list[list[int]]:
    factors = [[n, 2] for n in range((x // 4) * 4 + 2, y + 1, 4)]
    
    # add factor to list for every multiple of factor
    for fac in range(3, isqrt(y + 1)):
        # get first multiple of factor above x: 2 mod 4 as lower limit
        lower_limit = ((x - 1) // fac + 1) * fac

        for _ in range(4):
            if lower_limit % 4 == 2:
                break
            lower_limit += fac
        else:  # if no multiple x where x = 2 mod 4 is found, do not check
            continue
        
        # fill up array with multiples
        step = lcm(fac, 4)
        for mult in range(lower_limit, y + 1, step):
            factors[(mult-x) // 4].append(fac)

    return factors


@cache
# determines if num is prime according to the constraints of problem 357
def isprime_357(num: int) -> bool:
    if num % 3 == 0:  # for 3 (can't be divisible by 2)
        return False

    for i in range(5, isqrt(num) + 1, 6):  # for 6k +- 1
        if num % i == 0 or num % (i + 2) == 0:
            return False
    return True


# returns False if any d + n / d is not prime, True otherwise
def dnd_prime(factors: list[int]) -> bool:
    n = factors[0]  # get n from the factors (factor pair 1 * n)
    return all(isprime_357(factor + n // factor) for factor in factors)


def main():
    # declare variables
    limit = 100_000_000
    sum_n = 3  # loop will only detect even numbers (excluding 1 and 2)
    block_size = 1_000_000

    # loop through all even ints below limit
    for lower_m in range(limit // block_size):
        # generate list of factors
        factor_list = generate_divisor_list_357(
            lower_m * block_size + 2, (lower_m + 1) * block_size)
        sum_n += sum(max(factors) for factors in factor_list
            if dnd_prime(factors))
        
        # progress tracker
        print(f"block: {(lower_m + 1) * block_size}, sum: {sum_n}")  

    # print result
    print(f"Sum of all n up to {limit}: {sum_n}")


if __name__ == "__main__":
    main()
  