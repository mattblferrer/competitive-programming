import math

# Sieve of Eratosthenes
limit = 2000000
sumPrimes = 0
listPrimes = [True for i in range(2, limit)]  # initialize array of booleans up to the limit

for i in range(2,math.ceil(limit**0.5)):
    multiple = i**2  # initialize to i^2 for optimization
    while multiple < limit:
        listPrimes[multiple - 2] = False  # assign multiples of i as not being prime
        multiple += i

for i in range(limit-2):
    if listPrimes[i]:
        sumPrimes += (i+2)  # add prime to sum (adjusted by 2)

print(sumPrimes)