import math

# Sieve of Eratosthenes
limit = 2000000
sumPrimes = 0
listPrimes = [True for i in range(2, limit)]  # initialize array of booleans up to the limit

# for 2
multiple = 4
while multiple < limit:
    listPrimes[multiple - 2] = False
    multiple += 2

# for odd numbers
for i in range(3, math.ceil(limit ** 0.5), 2):
    multiple = i ** 2  # initialize to i^2 for optimization
    while multiple < limit:
        listPrimes[multiple - 2] = False  # assign multiples of i as not being prime
        multiple += i

# sum up all primes found by sieve
for i in range(limit - 2):
    if listPrimes[i]:
        sumPrimes += (i + 2)  # add prime to sum (adjusted by 2)

print(sumPrimes)
