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


# declare variables
limit = 10000
ctr = 2  # for primes 2 and 3
n = 3

# loop through first k primes
while ctr <= limit:
    n += 2
    if isprime(n):
        ctr += 1

# print result
print(n)
