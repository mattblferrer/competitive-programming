def number_factors(num: int) -> int:  # returns the number of factors of num
    total_factors = 1

    while num % 2 == 0:  # check for even factors
        total_factors += 1
        num //= 2

    if num % 3 == 0:  # for multiples of 3
        power = 1
        while num % 3 == 0:
            power += 1
            num //= 3
        total_factors *= power

    for i in range(5, int(num**0.5)+3, 6):  # for 6k +- 1
        for j in [0, 2]:
            power = 1
            while num % (i+j) == 0:
                power += 1
                num //= (i+j)
            total_factors *= power

    return total_factors


# declare variables
tri, ctr = 1, 2  # triangular number

while number_factors(tri) <= 500:
    tri += ctr  # generate the next triangular number
    ctr += 1

# print result
print(tri)
