# determines if num is prime
def isprime(num):
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        for j in [-1, 1]:
            if num % (i + j) == 0:
                return False
    return True


# generate next prime
def next_prime(num):
    while True:
        num += 2
        if isprime(num):
            return num


# declare variables
limit = 1000000
currPrime = 3
n = 2

# main loop
while n < limit:
    n *= currPrime  # calculate next primorial
    checkPrime = currPrime
    currPrime = next_prime(currPrime)

# print output
print(f"The value of n for which n/phi(n) is at a maximum is {n // checkPrime}")
