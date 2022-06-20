n = 600851475143  # given n
sqrtn = int(n**0.5)
primeFactors = []

for i in range(2, sqrtn):  # only have to check for factors below sqrt(n)
    if n % i == 0:
        primeFactors.append(i)
        n //= i

print(primeFactors)