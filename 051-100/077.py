# returns the number of ways to partition a number into different sets (same as change_ways function)
def change_ways(coin_set, num):
    if num == 0:  # 1 way to make change with 0 money (no coins)
        return 1
    elif num < 0:  # no ways to make change for less than 0 money
        return 0
    elif len(coin_set) == 0:  # no ways to make change with no choice of coins
        return 0
    else:
        # recursive formula given number of ways to give change with smaller set of change
        return change_ways(coin_set[:-1], num) + change_ways(coin_set, num-coin_set[-1])


# determines if num is prime
def isprime(num):
    for i in range(2, int(num**0.5+1)):  # for odd numbers
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
primeList = [2, 3, 5, 7]
currentNumber = 10
numberOfWays = 5

# main loop
while numberOfWays <= 5000:
    currentNumber += 1

    # update prime list
    if isprime(currentNumber):
        primeList.append(currentNumber)

    # calculate number of ways to write number as a sum of primes
    numberOfWays = change_ways(primeList, currentNumber)

# print result
print(currentNumber, "can be written in", numberOfWays, "ways")
