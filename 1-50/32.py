"""
We only have to check for numbers from 1000 to 10000
"""


# checks if a number num is pandigital
def pandigital_check(num):
    digits_used = [int(digit) for digit in str(num)]

    if sorted(list(digits_used)) == list(range(1, 10)):
        return True
    return False


# returns the factors of num in pairs (non-repeating)
def factorize(num):
    factors = set()
    factors.add((1, num))

    for i in range(2, int(num ** 0.5) + 1):  # only have to check for odd factors up to sqrt(n)
        if num % i == 0:
            factors.add((i, num//i))

    return factors


# returns the multiplicand, multiplier, and product as a concatenated number
def conc_factors(num):
    factors = factorize(num)
    string_list = [str(num)]*len(factors)
    ctr = 0  # counter for iterating through factors

    for factor in factors:  # two factors (tuple) at a time
        string_list[ctr] += str(factor[0]) + str(factor[1])
        ctr += 1

    return string_list


# declare variables
products = []  # products that can be written as 1 to 9 pandigital
productSum = 0

# main loop
for i in range(1000, 10000):
    identities = conc_factors(i)

    for identity in identities:
        if pandigital_check(identity):
            products.append(i)
            productSum += i
            break

# print output
print("The sum of all products is", productSum)
