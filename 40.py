"""
PLAN:
1-digit numbers have 1*9 = 9 digits
2-digit numbers have 2*90 = 180 digits
3-digit numbers have 3*900 = 2700 digits
and so on.
"""


# given parameters
highestIndexExponent = 6
highestIndex = 10**highestIndexExponent

# declaring variables
integers = []  # list of integer indices
digits = []  # list of digits
digitProduct = 1

# calculating points where n-digit numbers end and (n+1)-digit numbers begin
nDigitTransitions = []
n = highestIndex
transitionPoint = 0
ctr = 1
while n > 0:
    transitionPoint += ctr*(9*10**(ctr-1))
    nDigitTransitions.append(transitionPoint)
    n -= ctr*(9*10**(ctr-1))
    ctr += 1

# generating d n
for i in range(highestIndexExponent+1):  # iterating through exponents 10^i
    currentIndex = 10**i
    numberOfDigits = 1

    # get number of digits of integers needed to calculate constant to index
    while nDigitTransitions[numberOfDigits-1] < currentIndex:
        numberOfDigits += 1

    # calculate which integer the index lands on
    if currentIndex > nDigitTransitions[0]:
        indexAdjusted = currentIndex - nDigitTransitions[numberOfDigits-2] - 1
        integer = indexAdjusted // numberOfDigits + 10 ** (numberOfDigits - 1)  # which integer?
        digit = indexAdjusted % numberOfDigits  # which digit?
    else:
        indexAdjusted = currentIndex
        integer = indexAdjusted // numberOfDigits  # which integer?
        digit = indexAdjusted % numberOfDigits  # which digit?
    integers.append(integer)
    digits.append(digit)

for i in range(len(integers)):
    intDigits = [int(a) for a in str(integers[i])]
    digitProduct *= intDigits[digits[i]]

# final output
print(digitProduct)

