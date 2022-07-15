from math import sqrt


# determines if num is prime
def isprime(num):
    if num % 2 == 0:  # for even numbers
        return False

    for i in range(3, int(sqrt(num))+1, 2):  # for odd numbers
        if num % i == 0:
            return False
    return True


# generate next prime
def next_prime(num):
    while True:
        num += 2
        if isprime(num):
            return num


# declare variables
primes = [2]
limit = 1000000
currentPrime = 3
maximumPrime = 3
maximumLength = 0  # length of longest sum of consecutive primes

# main loop
while currentPrime < limit:
    for startingPrime in range(len(primes)//500+1):
        primeSum = 0
        currentLength = 0

        # loop through consecutive primes
        while primeSum < currentPrime:
            try:
                primeSum += primes[startingPrime]
                currentLength += 1
            except IndexError:
                break

            startingPrime += 1

        # check if consecutive prime sum is equal
        if primeSum == currentPrime:
            if maximumLength < currentLength:
                maximumLength = currentLength
                maximumPrime = currentPrime

    # next prime
    primes.append(currentPrime)
    currentPrime = next_prime(currentPrime)

# print result
print("The prime below 1 million that can be written as the sum of the most consecutive"
      "primes is", maximumPrime, maximumLength)
