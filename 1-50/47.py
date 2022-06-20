def num_prime_factors(num):  # returns the number of distinct prime factors of num
    factorlist = set()
    sqrtn = int(num**0.5)

    for i in range(2, sqrtn+1):  # only have to check for factors below sqrt(n)
        while num % i == 0:
            factorlist.add(i)
            num //= i
    if num > sqrtn:
        factorlist.add(num)

    # length of factor list
    return len(factorlist)


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
print("The first of these numbers is", i-3)  # print the first of these numbers (i-3, i-2, i-1, i)
