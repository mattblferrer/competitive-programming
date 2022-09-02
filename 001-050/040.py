"""
PLAN:
1-digit numbers have 1*9 = 9 digits
2-digit numbers have 2*90 = 180 digits
3-digit numbers have 3*900 = 2700 digits
and so on.
"""
from math import prod


# given parameters
highestIndexExponent = 6
n = 10**highestIndexExponent

# declaring variables
integers = []  # list of integer indices
digits = []  # list of digits
digitProduct = 1

# calculating points where n-digit numbers end and (n+1)-digit numbers begin
nDigitTransitions = []
transitionPoint = 0
ctr = 1

while n > transitionPoint:
    transitionPoint += ctr*(9*10**(ctr-1))
    nDigitTransitions.append(transitionPoint)
    ctr += 1

# generating d_n
for i in range(highestIndexExponent+1):  # iterating through exponents 10^i
    currentIndex = 10**i
    numberOfDigits = next(i for i, v in enumerate(nDigitTransitions, start=1) if v > currentIndex)

    # calculate which integer the index lands on
    if currentIndex > nDigitTransitions[0]:  # if more than 1 digit
        indexAdjusted = currentIndex - nDigitTransitions[numberOfDigits-2] - 1
        integer = indexAdjusted // numberOfDigits + 10 ** (numberOfDigits - 1)  # which integer?
        digit = indexAdjusted % numberOfDigits  # which digit?

    else:  # if 1 digit
        indexAdjusted = currentIndex
        integer = indexAdjusted // numberOfDigits  # which integer?
        digit = indexAdjusted % numberOfDigits  # which digit?

    # append int, digit of int pairs of powers of 10
    integers.append(integer)
    digits.append(digit)

# multiply i'th digits of n together
digitProduct = prod(int(str(n)[digits[i]]) for i, n in enumerate(integers)) 

# final output
print(digitProduct)

