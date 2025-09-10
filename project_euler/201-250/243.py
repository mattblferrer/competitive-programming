# returns the prime factors of num (non-repeating)
def prime_factorize(num):
    factors = set()

    for i in [2, 3]:
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        for j in [-1, 1]:
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)

    if num != 1:
        factors.add(num)

    return factors


# returns the Euler's totient of the number num using Euler's product formula
def totient(num):
    p_factors = prime_factorize(num)
    phi = num  # totient
    for factor in p_factors:
        phi = phi * (factor-1)//factor

    return phi 


# determines if num is prime
def isprime(num):
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# generate next prime
def next_prime(num):
    while True:
        num += 2
        if isprime(num) == 1:
            return num


# declare variables
targetRd = 15499/94744
d = 12
prime = 5
currPrimorial = 6  # primorial of 3
nextPrimorial = 30  # primorial of 5

# main loop
while True:
    phi = totient(d)
    res = phi / (d-1)  # resilience
    
    if res < targetRd:  # check if current resilience is lower
        break

    if d == nextPrimorial:  # check if primorial is reached
        prime = next_prime(prime)
        currPrimorial = nextPrimorial
        nextPrimorial *= prime

    d += currPrimorial

# print result
print("Smallest denominator d:", d)
