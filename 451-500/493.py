"""
Picking 20 balls from 70 balls, the minimum number of colors that can be chosen
is 2. The number of possible ways to pick 20 balls from 70 balls is 70 choose 20

The number of probabilities to pick:
2 colors = 20 choose 20
3 colors = 30 choose 20 - 20 choose 20
,because 30 choose 20 is the number of possible ways to pick *at most* 3 colors.

This pattern continues up to 7 colors = 70 choose 20 - 60 choose 20.
This is a telescoping sum leaving us with the expected number of distinct colors
being:

7 * (70 choose 20 - 60 choose 20) / 70 choose 20.
"""


# calculates the factorial of n
from math import comb


def factorial(n):
    fac = 1  # factorial
    for i in range(1, n+1):
        fac *= i
    return fac


# the function n choose r
def combination(n, r):
    return factorial(n)//(factorial(r)*factorial(n-r))


# calculate and print result
answer = 7*(combination(70, 20) - combination(60, 20))/(combination(70, 20))
print("{:.9f}".format(answer))
