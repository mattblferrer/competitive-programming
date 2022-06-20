import math


# reduces fraction to its lowest terms
def reduce(numerator, denominator):
    # divide numerator, denominator by their GCD
    gcd = math.gcd(numerator, denominator)
    numerator //= gcd
    denominator //= gcd

    return numerator, denominator

# TODO
