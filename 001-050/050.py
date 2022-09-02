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
print(f"The prime below 1 million that can be written as the sum of the most consecutive"
      "primes is {maximumPrime}, length: {maximumLength}")
