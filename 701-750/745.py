"""
CODE FOR CHECKING:

from math import sqrt


# returns the highest perfect square that divides num
def highest_square_div(num):
    square = 1

    while num % 4 == 0:  # for only even square
        square *= 4
        num //= 4

    # for odd number squares
    for i in range(3, int(num ** 0.5) + 1, 2):
        while num % (i*i) == 0:
            square *= (i*i)
            num //= (i*i)

    if sqrt(num).is_integer():
        square *= num

    return square


sSum = 0
for i in range(1, 101):
    high_sqr = highest_square_div(i)
    sSum += high_sqr
    # print(i, high_sqr, sSum)

print(sSum)
"""


# TODO
