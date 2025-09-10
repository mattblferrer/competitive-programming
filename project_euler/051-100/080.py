from decimal import *
from math import sqrt

# decimals with 100 digits of precision + 5 for wiggle room for imprecision
getcontext().prec = 105  


# returns an array of the decimal expansion of the square root of n
def sqrt_decimal_expansion(n: int) -> list[int]:
    ans = Decimal(n).sqrt() # convert to Decimal for higher precision

    # return array of list of 100 digits of sqrt(n)
    return [int(digit) for digit in str(ans) if digit != "."][:100]


# main loop
digitalSum = 0

for i in range(1, 101):
    if not sqrt(i).is_integer():   # perfect square check
        digitalSum += sum(sqrt_decimal_expansion(i))

# print result
print(f"The digital sum of the square roots of the first one hundred natural \
numbers is {digitalSum}")
