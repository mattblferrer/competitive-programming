# returns the prime factors of num (repeating)
def prime_factorize(num):
    factors = []

    while num % 2 == 0:  # for only even prime
        factors.append(2)
        num //= 2

    while num % 3 == 0:  # for 3
        factors.append(3)
        num //= 3

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        while num % (i-1) == 0:
            factors.append(i-1)
            num //= (i-1)
            
        while num % (i+1) == 0:
            factors.append(i+1)
            num //= (i+1)

    if num != 1:
        factors.append(num)

    return factors


n = 600851475143  # given n
print(prime_factorize(n))
