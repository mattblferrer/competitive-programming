from functools import cache


@cache
# returns the number of ways to partition a number into different sets 
# (same as change_ways function)
def change_ways(coin_set: tuple[int], num: int) -> int:
    if num == 0:  # 1 way to make change with 0 money (no coins)
        return 1
    elif num < 0:  # no ways to make change for less than 0 money
        return 0
    elif len(coin_set) == 0:  # no ways to make change with no choice of coins
        return 0
    else:
        # recursive formula given number of ways to give change with smaller 
        # set of change
        return (change_ways(coin_set[:-1], num) 
            + change_ways(coin_set, num-coin_set[-1]))


# determines if num is prime
def isprime(num: int) -> bool:
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(5, int(num ** 0.5)+3, 6):  # for 6k +- 1
        if num % i == 0 or num % (i+2) == 0:
            return False
    return True


# generate next prime
def next_prime(num: int) -> int:
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
    numberOfWays = change_ways(tuple(primeList), currentNumber)

# print result
print(f"{currentNumber} can be written in {numberOfWays} ways")
