# returns the prime factors of num (repeating)
def prime_factorize(num):
    factors = []

    for i in [2, 3]:
        while num % i == 0:  # for only even prime
            factors.append(i)
            num //= i

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        for j in [-1, 1]:
            while num % (i+j) == 0:
                factors.append(i+j)
                num //= (i+j)

    if num != 1:
        factors.append(num)

    return factors


n = 600851475143  # given n
print(prime_factorize(n))
