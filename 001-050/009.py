"""
For any given integer m and n, m > n > 0: 
a = m^2 - n^2
b = 2mn
c = m^2 + n^2,

is a valid Pythagorean triple
"""
from math import prod


def find_triple() -> tuple[int]:
    sumABC = 1000  # given a+b+c = 1000
    limit = 100  # loop iteration limit

    for m in range(1, limit):
        for n in range(1, m):
            # calculate a, b, c based on iterated values of m, n
            a = m**2 - n**2
            b = 2*m*n
            c = m**2 + n**2

            if a + b + c == sumABC:
                return a, b, c


# print result
print((triple := find_triple()), prod(triple))  # print product abc
