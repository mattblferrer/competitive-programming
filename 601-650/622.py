# returns the factors of num (non-repeating)
def factorize(num: int) -> set:
    factors = set()
    factors.add(1)
    factors.add(num)

    for i in range(2, int(num ** 0.5) + 1):  # only have to check for odd factors up to sqrt(n)
        if num % i == 0:
            factors.add(i)
            factors.add(num // i)

    return factors


# declare variables
s = 60
s_sum = 0
checked_values = set()

# loop through all lower s values to check for duplicates
for check in range(1, s):
    print(check)  # track progress
    for factor in factorize(2**check - 1):
        checked_values.add(factor + 1)

# loop through all n where 2^s mod (n-1) = 1
for factor in factorize(2**s - 1):
    if (factor + 1) not in checked_values:
        s_sum += (factor + 1)

# print result
print(f"Sum of all values of n, s(n) = {s}: {s_sum}")
