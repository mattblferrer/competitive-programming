def num_prime_factors(num):  # returns the number of distinct prime factors of num
    factors = set()

    for i in [2, 3]:
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        for j in [-1, 1]:
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)

    if num != 1:
        factors.add(num)

    return len(factors)  # return number of factors


# declaring variables
consecutiveRun = 0  # length of run of 4 distinct prime factors
i = 646  # we can start here as given in the problem

# finding the first 4 consecutive integers to have 4 distinct prime factors
while consecutiveRun < 4:
    i += 1
    if num_prime_factors(i) == 4:
        consecutiveRun += 1
    else:
        consecutiveRun = 0

# final output
print(f"The first of these numbers is {i-3}")  # print the first of these numbers (i-3, i-2, i-1, i)
