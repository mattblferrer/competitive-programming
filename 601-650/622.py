# returns the factors of num (non-repeating)
def factorize(num: int) -> set:
    factors = {1, num}

    for i in range(2, int(num ** 0.5) + 1):  # only have to check for odd factors up to sqrt(n)
        if num % i == 0:
            factors.update({i, num // i})

    return factors


# declare variables
s = 60
checked_values = set()

# loop through all lower s values (factors of s) to check for duplicates
for check in sorted(list(factorize(s)))[:-1]:
    print(check)  # track progress
    checked_values.update({f + 1 for f in factorize(2**check - 1)})

# loop through all n where 2^s mod (n-1) = 1
s_sum = sum(f + 1 for f in factorize(2**s - 1) if (f + 1) not in checked_values)

# print result
print(f"Sum of all values of n, s(n) = {s}: {s_sum}")
