from collections import Counter


# returns the prime factors of num (non-repeating)
def prime_factorize(num):
    factors = set()

    while num % 2 == 0:  # for only even prime
        factors.add(2)
        num //= 2

    while num % 3 == 0:  # for 3
        factors.add(3)
        num //= 3

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        while num % (i-1) == 0:
            factors.add(i-1)
            num //= (i-1)
            
        while num % (i+1) == 0:
            factors.add(i+1)
            num //= (i+1)

    if num != 1:
        factors.add(num)

    return factors


# returns the Euler's totient of the number num using Euler's product formula
def totient(num, p_factors):
    phi = num  # totient
    for factor in p_factors:
        phi = phi * (factor-1)//factor

    return phi


# declare variables
limit = 10**7
minimumRatio = 100
minimumN = 0

# main loop
for i in range(1, limit, 2):  # number with min ratio cannot have factor of 2
    prime_factors = prime_factorize(i)

    # if i is prime, there is no need to calculate it
    if len(prime_factors) != 1:
        # count digits
        t = totient(i, prime_factors)
        t_digits = Counter([int(digit) for digit in str(t)])
        n_digits = Counter([int(digit) for digit in str(i)])

        # if totient is a permutation of the original number
        if t_digits == n_digits:
            ratio = i/t
            if minimumRatio > ratio:
                minimumRatio = ratio
                minimumN = i

# print result
print("The value of n for which phi(n) is a permutation and gives the minimum ratio is", minimumN)
print("The ratio n/phi(n) is", minimumRatio)
