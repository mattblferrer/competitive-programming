from math import sqrt
from functools import cache


@cache
# determines if num is prime
def isprime(num: int) -> bool:
    if num < 2:  # inputs can be negative
        return False

    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(5, int(sqrt(num))+3, 6):  # for 6k +- 1
        if num % i == 0 or num % (i+2) == 0:
            return False
    return True


# given parameters
a, b = 1000, 1000

# output variables
max_primes = 0
max_i, max_j = 0, 0

# calculate quadratic expression
for i in range(-a, a+1):
    for j in range(-b, b+1):
        for k in range(0, j+1):  # only have to check for n up to b+1
            current_quad = (k+i) * k + j  # compute quadratic
            if not isprime(current_quad):
                if k > max_primes:
                    # store values a, b, and the length of the prime run
                    max_i, max_j, max_primes = i, j, k
                break

# final output
print(f"Maximum number of primes: {max_primes}")
print(f"a, b: {max_i}, {max_j}")
print(f"Product: {max_i * max_j}")
