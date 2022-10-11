"""
We only have to check for numbers from 1000 to 10000
"""


# checks if a number num is pandigital
def pandigital_check(num: int) -> bool:
    digits_used = {int(digit) for digit in str(num)}

    if digits_used == set(range(1, 10)):
        return True
    return False


# returns the factors of num in pairs (non-repeating)
def factorize(num: int) -> set[int]:
    factors = set()
    factors.add((1, num))

    for i in range(2, int(num ** 0.5) + 1):  # only have to check for odd factors up to sqrt(n)
        if num % i == 0:
            factors.add((i, num//i))

    return factors


# returns the multiplicand, multiplier, and product as a concatenated number
def conc_factors(num: int) -> list[str]:
    factors = factorize(num)
    string_list = [str(num)]*len(factors)

    for ctr, factor in enumerate(factors):  # two factors (tuple) at a time
        string_list[ctr] += f"{factor[0]}{factor[1]}"

    return string_list


# declare variables
products = []  # products that can be written as 1 to 9 pandigital
product_sum = 0

# main loop
for i in range(1000, 10000):
    identities = conc_factors(i)

    for identity in identities:
        if pandigital_check(identity):
            products.append(i)
            product_sum += i
            break

# print output
print(f"The sum of all products is {product_sum}")
