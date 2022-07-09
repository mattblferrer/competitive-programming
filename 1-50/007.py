n = 10001
ctr = 2
prime = 3
primeList = []

while ctr < n:
    prime += 2
    isPrime = True
    for i in range(2, int(prime**0.5)+1):
        if prime % i == 0:
            isPrime = False
    if isPrime:
        primeList.append(prime)
        ctr += 1

print(prime)
print(primeList)
