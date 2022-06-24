# determines if num is prime
def isprime(num):
    if num % 2 == 0:  # for even numbers
        return False

    for i in range(3, int(num**0.5+1), 2):  # for odd numbers
        if num % i == 0:
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
    while num > 0:
        length = len(str(num)) - 1  # highest power of 10 smaller than num

        # truncating number from left
        if isprime(num):
            num = num % (10**length)
        else:
            return False
    return True


# determine if prime is truncatable from right to left
def is_right_truncatable(num):
    while num > 0:
        # truncating number from right
        if isprime(num):
            num = num // 10
        else:
            return False
    return True


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
