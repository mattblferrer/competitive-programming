def number_factors(num):  # returns the number of factors of num
    factorlist = []

    for i in range(2, int(num**0.5)+1):  # only have to check for factors up to sqrt(n)
        if num % i == 0:
            factorlist.append(i)
            factorlist.append(num // i)

    # length of factor list
    return len(factorlist)


tri = 1  # triangular number
ctr = 2  # counter
while number_factors(tri) <= 500:
    # generate the next triangular number
    tri += ctr
    ctr += 1

print(tri)
