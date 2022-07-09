"""
Length of Farey sequence n = 1 + sum of totient functions from 1 to n
"""


# returns the prime factors of num (non-repeating)
def prime_factorize(num):
    factors = set()

    while num % 2 == 0:  # for only even prime
        factors.add(2)
        num //= 2

    for i in range(3, int(num ** 0.5) + 1, 2):  # only have to check for odd factors up to sqrt(n)
        while num % i == 0:
            factors.add(i)
            num //= i

    if num != 1:
        factors.add(num)

    return factors


# returns the Euler's totient of the number num using Euler's product formula
def totient(num):
    p_factors = prime_factorize(num)
    phi = num  # totient
    for factor in p_factors:
        phi = phi * (factor-1)//factor

    return phi


# declare variables
d = 1000000
totientSum = 1

# main loop
for i in range(1, d+1):
    totientSum += totient(i)

# print result
print(totientSum - 2)  # not counting 0/1, 1/1
