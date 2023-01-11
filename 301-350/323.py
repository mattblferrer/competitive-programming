"""
CODE FOR CHECKING:

from random import getrandbits

ctr = 0
n = 100_000
for i in range(n):
    x = 0  # x0
    while x != 2 ** 32 - 1:
        y = getrandbits(32)
        x = x | y
        ctr += 1

print(ctr / n)
"""
from fractions import Fraction


def main():
    # start with fraction for infinite precision calculation
    sum_value = Fraction(1, 1)

    # sum expected values for each turn
    for i in range(1, 1000):
        sum_value += (Fraction(1, 1) - (Fraction(2 ** i - 1, 2 ** i)) ** 32)

    # print result
    print(float(sum_value))


if __name__ == "__main__":
    main()
