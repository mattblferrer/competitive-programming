from math import gcd, lcm


# reduces fraction to its lowest terms
def reduce(numerator: int, denominator: int) -> tuple[int]:
    # divide numerator, denominator by their GCD
    frac_gcd = gcd(numerator, denominator)
    numerator //= frac_gcd
    denominator //= frac_gcd

    return numerator, denominator


# adds two fractions together
def add_fraction(n1: int, d1: int, n2: int, d2: int) -> tuple[int]:
    d = lcm(d1, d2)  # calculate new denominators

    # calculate new numerators
    n1 *= (d // d1)
    n2 *= (d // d2)

    return reduce(n1 + n2, d)


# returns the number of ways 1/2 can be expressed as a sum of inverse squares
# n^2 from 2 to n
def half_inverse_sqr(limit: int) -> int:
    ways = 0
    squares = [i*i for i in range(limit+1)]
    n, d = 0, 1  # numerator and denominator
    is_used = [False]*(limit+1)  # marks which numbers were used in the expansion

    # TODO function

# declare variables
n = 80
ways = 0
print(half_inverse_sqr(n))

# print result
print(ways)
