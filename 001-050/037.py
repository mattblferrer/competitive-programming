from math import sqrt


# determines if num is prime
def isprime(num):
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


# generate next prime
def next_prime(num):
    while True:
        num += 2
        if isprime(num):
            return num


# determine if prime is truncatable from left to right
def is_left_truncatable(num):
    while num > 10:
        length = len(str(num)) - 1  # highest power of 10 smaller than num

        # truncating number from left
        if isprime(num):
            num = num % (10**length)
        else:
            return False

    if num in [2, 3, 5, 7]:
        return True
    return False


# determine if prime is truncatable from right to left
def is_right_truncatable(num):
    while num > 10:
        # truncating number from right
        if isprime(num):
            num = num // 10
        else:
            return False

    if num in [2, 3, 5, 7]:
        return True
    return False


# define variables
currentPrime = 11
truncatableSum = 0  # output
numberOfPrimes = 0  # we need to have 11 primes

while numberOfPrimes < 11:
    # iterate through primes
    currentPrime = next_prime(currentPrime)

    # check if prime is truncatable from left and from right
    if is_left_truncatable(currentPrime) and is_right_truncatable(currentPrime):
        numberOfPrimes += 1
        truncatableSum += currentPrime

print("The sum of all eleven left and right truncatable primes is", truncatableSum)
