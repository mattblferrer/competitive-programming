# determines if num is prime
def isprime(num):
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# generate next prime
def next_prime(num):
    while True:
        num += 1
        if isprime(num):
            return num


# declare variables
limit = 5*10**7  # 50 million
expressibleNumbers = set()
a = 2

# calculate root
limit_4 = int(limit**(1/4)) + 1

# iterate through all a, b, c for which a^4 + b^3 + c^2 < limit
while a < limit_4:
    # calculate root, reset b
    limit_3 = int((limit - a**4)**(1/3)) + 1
    b = 2

    while b < limit_3:
        # calculate root, reset c
        limit_2 = int((limit - a**3)**(1/2)) + 1
        c = 2

        while c < limit_2:
            # calculate sum and compare against existing set
            n = a**4+b**3+c**2

            if n < limit and n not in expressibleNumbers:
                expressibleNumbers.add(n)
            c = next_prime(c)

        b = next_prime(b)

    a = next_prime(a)

# print result
print(len(expressibleNumbers))
