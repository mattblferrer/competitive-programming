from math import sqrt


n = 10001
ctr = 2
prime = 3

while ctr < n:
    prime += 2
    isPrime = True

    for i in range(3, int(sqrt(prime))+1, 2):  # check odd only
        if prime % i == 0:
            isPrime = False

    if isPrime:
        ctr += 1

print(prime)
