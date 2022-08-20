# declare variables
power = 7830457
factor = 28433
mod = 10**10

# calculate prime
prime = (factor * pow(2, power, mod) + 1) % mod

# print result
print("The last 10 digits of this prime number are", prime)
