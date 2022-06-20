# determines if n is prime
def isprime(n):
    if n < 2:
        return False
    else:
        for i in range(2, int(n**0.5+1)):  # for odd numbers
            if n % i == 0:
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
