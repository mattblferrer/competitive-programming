def number_factors(num):  # returns the number of factors of num
    total_factors = 1

    while num % 2 == 0:  # check for even factors
        total_factors += 1
        num //= 2

    while num % 3 == 0:  # for multiples of 3
        power = 1
        while num % 3 == 0:
            power += 1
            num //= 3
        total_factors *= power

    for i in range(5, int(num**0.5)+3, 6):  # for 6k +- 1
        # 6k - 1
        power = 1
        while num % i == 0:
            power += 1
            num //= i
        total_factors *= power

        # 6k + 1
        power = 1
        while num % (i+2) == 0:
            power += 1
            num //= (i+2)
        total_factors *= power

    return total_factors


tri = 1  # triangular number
ctr = 2  # counter
while number_factors(tri) <= 500:
    # generate the next triangular number
    tri += ctr
    ctr += 1

print(tri)
