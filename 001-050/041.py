"""
The prime can't have 9 digits, as the sum of the digits would be 45, divisible by 9.
The prime can't have 8 digits either, for the same reason.
"""

from itertools import permutations
from math import sqrt


# determines if num is prime
def isprime(num):
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(sqrt(num))+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# generate list of 1 to 7 pandigital numbers in descending order
allDigits = "7654321"
pandigitalList = [int(''.join(digits)) for digits in permutations(allDigits)]

# iterate through all pandigital numbers in list
prime = next(i for i in pandigitalList if isprime(i))

# print result
print(f"The largest n-digit pandigital prime that exists is: {prime}")

