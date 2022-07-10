def number_factors(num):  # returns the number of factors of num
    total_factors = 1

    while num % 2 == 0:  # check for even factors
        total_factors += 1
        num //= 2

    for i in range(3, int(num**0.5)+1, 2):  # only have to check for odd factors up to sqrt(n)
        power = 1
        while num % i == 0:
            power += 1
            num //= i

        total_factors *= power

    return total_factors


tri = 1  # triangular number
ctr = 2  # counter
while number_factors(tri) <= 500:
    # generate the next triangular number
    tri += ctr
    ctr += 1

print(tri)
