from functools import cache


# returns a list of all the factors of n from x to y
def generate_factor_list(x: int, y: int) -> list[list[int]]:
    factors = [[] for _ in range(y-x+1)]
    
    # add factor to list for every multiple of factor
    for fac in range(1, y+1):
        # get first multiple of factor above x as lower limit
        for mult in range((x-1) // fac * fac + fac, y+1, fac):
            factors[mult-x].append(fac)

    return factors


@cache
# determines if num is prime
def isprime(num: int) -> bool:
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# returns False if any d+n/d is not prime, True otherwise
def dnd_prime(factors: list) -> bool:
    factor_num = len(factors) - 1
    for i in range(factor_num // 2 + 1):
        if not isprime(factors[i] + factors[factor_num - i]):
            return False

    return True


# declare variables
limit = 100_000_000
sumN = 1  # loop will only detect even numbers (excluding 1)
block_size = 250_000

# loop through all even ints below limit
for lower_m in range(limit // block_size):
    # generate list of factors
    factor_list = generate_factor_list(lower_m * block_size + 2, (lower_m+1) * block_size)

    for factors in factor_list[::2]:
        if dnd_prime(factors):
            sumN += factors[-1]
    
    print(lower_m)  # progress tracker

# print result
print(sumN)
