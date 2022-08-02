from math import sqrt


# determines if num is prime
def isprime(num):
    if num < 2:  # inputs can be negative
        return False

    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(sqrt(num))+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# given parameters
a = 1000
b = 1000

# output variables
maxPrimes = 0
maxI = 0
maxJ = 0

# calculate quadratic expression
for i in range(-a, a+1):
    for j in range(-b, b+1):
        for k in range(0, j+1):  # only have to check for n up to b+1
            currentQuad = k**2 + i*k + j  # compute quadratic
            if not isprime(currentQuad):
                if k > maxPrimes:
                    # store values a, b, and the length of the prime run
                    maxPrimes = k
                    maxI = i
                    maxJ = j
                break

# final output
print("Maximum number of primes: ", maxPrimes)
print("a, b:", maxI, maxJ)
print("Product: ", maxI*maxJ)
