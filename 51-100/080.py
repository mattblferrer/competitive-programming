from decimal import *
import math
getcontext().prec = 105  # decimals with 100 digits of precision + 5 for wiggle room for imprecision


# returns an array of the decimal expansion of the square root of n
def sqrt_decimal_expansion(n):
    n = Decimal(n)  # convert to Decimal for higher precision
    ans = n.sqrt()

    # return array of list of 100 digits of sqrt(n)
    return [int(digit) for digit in str(Decimal(ans)) if digit in "1234567890"][:100]


# main loop
digitalSum = 0

for i in range(1, 101):
    if not math.sqrt(i).is_integer():   # perfect square check
        digitalSum += sum(sqrt_decimal_expansion(i))

# print result
print("The digital sum of the square roots of the first one hundred natural numbers is", digitalSum)
