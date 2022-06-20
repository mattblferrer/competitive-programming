# function that finds if a number is prime or not
def isprime(n):
    if n < 2:  # function can have negative inputs
        return False
    else:
        if n % 2 == 0:  # for number 2
            return False
        for i in range(2, int(n**0.5+1)):  # for odd numbers
            if n % i == 0:
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
