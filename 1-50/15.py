"""
To navigate an m x n grid, we can use permutations of m rights and n downs.
Therefore, the number of ways is (m+n)Cn
"""


def factorial(num):
    fac = 1  # factorial
    for i in range(1, num + 1):
        fac *= i
    return fac


# for m * n grid
m = 20
n = 20
numberOfWays = factorial(m + n) // (factorial(m) * factorial(n))  # from (m+n)Cn
print(numberOfWays)
