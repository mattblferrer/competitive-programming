from decimal import *
import math


# returns the array for the terms of the continued fraction of the sqrt of n
def continued_sqrt_fraction(n):
    getcontext().prec = n+20  # precision of the sqrt calculation
    n = Decimal(n)  # convert to decimal for increased precision
    sqrt_n = n.sqrt() - int(n.sqrt())  # fractional part only
    cont_frac = []
    remainders = []

    for i in range(int(n)):
        # check for repeats
        if float(sqrt_n) in remainders:
            return len(cont_frac)

        else:
            remainders.append(float(sqrt_n))

            # get integer part and take reciprocal again
            sqrt_n = 1 / sqrt_n
            cont_frac.append(int(sqrt_n))
            sqrt_n -= int(sqrt_n)

    return n-1


# declare variables
limit = 10000
oddPeriods = 0

# main loop
for i in range(2, limit+1):
    if not math.sqrt(i).is_integer():  # perfect square check
        terms = continued_sqrt_fraction(i)

        # odd check
        if terms % 2 == 1:
            oddPeriods += 1

# print result
print("The number of continued fractions with an odd period is", oddPeriods)
