# returns the prime factors of num
def prime_factorize(num):
    factors = []

    while num % 2 == 0:  # for only even prime
        factors.append(2)
        num //= 2

    for i in range(3, int(num ** 0.5) + 1, 2):  # only have to check for odd factors up to sqrt(n)
        while num % i == 0:
            factors.append(i)
            num //= i

    return factors


n = 600851475143  # given n
print(prime_factorize(n))
