from functools import cache
from itertools import product
from math import gcd


def reduce(numerator: int, denominator: int) -> tuple[int, int]:
    """reduces fraction to its lowest terms"""
    # divide numerator, denominator by their GCD
    frac_gcd = gcd(numerator, denominator)
    numerator //= frac_gcd
    denominator //= frac_gcd

    return numerator, denominator


@cache
def series_capacitor(c_1: tuple[int, int], c_2: tuple[int, int]) -> \
tuple[int, int]:
    """takes two fractional capacitances n1/d1 and n2/d2 as an integer tuple 
    and returns the capacitance of the two in series"""
    # take reciprocals of c_1, c_2
    (d_1, n_1) = c_1
    (d_2, n_2) = c_2

    return reduce(d_1 * d_2, n_1 * d_2 + d_1 * n_2)  # add and take reciprocal


@cache
def parallel_capacitor(c_1: tuple[int, int], c_2: tuple[int, int]) -> \
tuple[int, int]:
    """takes two fractional capacitances n1/d1 and n2/d2 as an integer tuple 
    and returns the capacitance of the two in parallel"""
    (n_1, d_1) = c_1
    (n_2, d_2) = c_2

    return reduce(n_1 * d_2 + d_1 * n_2, d_1 * d_2)


@cache
def capacitor_possibilities(n: int) -> set[tuple[int]]:
    """returns a set of all capacitances that can be formed with n 
    constant-capacitance capacitors (specified with variable base)"""
    capacitance_set = set()  # possible capacitances
    base = 1, 1  # base capacitance
     
    if n == 1:  # only one capacitor, return C of capacitor
        return {base}

    for i in range(1, n):
        for c_1, c_2 in product(capacitor_possibilities(n - i), 
            capacitor_possibilities(i)):
            capacitance_set.add(series_capacitor(c_1, c_2))
            capacitance_set.add(parallel_capacitor(c_1, c_2))

    return capacitance_set


def main():
    # declare variables
    limit = 18
    c_set = set()

    # for D(n): loop through all numbers of capacitors from 1 to n
    for i in range(1, limit + 1):  
        c_set.update(capacitor_possibilities(i))
        print(i, len(capacitor_possibilities(i)))

    # print result
    print(len(c_set))


if __name__ == "__main__":
    main()
