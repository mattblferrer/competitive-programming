"""
The prime can't have 9 digits, as the sum of the digits would be 45, divisible by 9.
The prime can't have 8 digits either, for the same reason.
"""

from itertools import permutations


# determines if num is prime
def isprime(num):
    for i in range(2, int(num**0.5+1)):  # for odd numbers
        if num % i == 0:
            return False
    return True


# generate list of 1 to 7 pandigital numbers in descending order
allDigits = "7654321"
pandigitalList = [int(''.join(digits)) for digits in list(permutations(allDigits))]

print("The 7 digit pandigital primes are: ")

# iterate through all pandigital numbers in list
for n in pandigitalList:
    if isprime(n):
        print(n)
