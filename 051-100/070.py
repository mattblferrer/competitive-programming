from collections import Counter


# returns the prime factors of num (non-repeating)
def prime_factorize(num: int) -> set:
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

    return factors


# returns the Euler's totient of the number num using Euler's product formula
def totient(num: int, p_factors: set) -> int:
    phi = num  # totient
    for factor in p_factors:
        phi = phi * (factor-1)//factor

    return phi


# declare variables
limit = 10**7
minimumRatio = 100
minimumN = 0

# main loop
for n in range(3, limit, 2):  # number with min ratio cannot have factor of 2
    prime_factors = prime_factorize(n)

    # if i is prime, there is no need to calculate it
    if len(prime_factors) != 1:
        # count digits
        t = totient(n, prime_factors)
        t_digits = Counter(str(t))
        n_digits = Counter(str(n))

        # if totient is a permutation of the original number
        if t_digits == n_digits:
            ratio = n/t
            if minimumRatio > ratio:
                minimumRatio = ratio
                minimumN = n

# print result
print("The value of n for which phi(n) is a permutation and gives the minimum ratio is", minimumN)
print("The ratio n/phi(n) is", minimumRatio)
