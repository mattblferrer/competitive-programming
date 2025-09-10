from math import log


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
        if isprime(num):
            return num


# declare variables
n = 20
answer = 2 ** int(log(n, 2))
prime = 3

# loop through primes up to n
while prime < n:
    answer *= prime ** int(log(n, prime))
    print(prime, answer)
    prime = next_prime(prime)

# print result
print(answer)
