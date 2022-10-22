from functools import cache
from math import isqrt


# returns a list of all the factors of n, n % 4 == 2 from x to y
def generate_factor_list_357(x: int, y: int) -> list[list[int]]:
    factors = [[1] for _ in range((x//4)*4 + 2, y+1, 4)]
    
    # add factor to list for every multiple of factor
    for fac in range(2, y+1):
        # get first multiple of factor above x as lower limit
        for mult in range((x-1) // fac * fac + fac, y+1, fac):
            if mult % 4 == 2:
                factors[(mult-x) // 4].append(fac)

    return factors


@cache
# determines if num is prime
def isprime(num: int) -> bool:
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(5, isqrt(num)+3, 6):  # for 6k +- 1
        if num % i == 0 or num % (i+2) == 0:
            return False
    return True


# returns False if any d+n/d is not prime, True otherwise
def dnd_prime(factors: list[int]) -> bool:
    factor_num = len(factors) - 1
    
    for i in range(factor_num // 2 + 1):
        if not isprime(factors[i] + factors[factor_num - i]): 
            return False
    return True


def main():
    # declare variables
    limit = 100_000_000
    sum_n = 1  # loop will only detect even numbers (excluding 1)
    block_size = 1_000_000

    # loop through all even ints below limit
    for lower_m in range(limit // block_size):
        # generate list of factors
        factor_list = generate_factor_list_357(
            lower_m * block_size + 2, (lower_m+1) * block_size)
        sum_n += sum(factors[-1] for factors in factor_list
            if dnd_prime(factors))
        
        # progress tracker
        print(f"block: {(lower_m + 1) * block_size}, sum: {sum_n}")  

    # print result
    print(f"Sum of all n up to {limit}: {sum_n}")


if __name__ == "__main__":
    main()
