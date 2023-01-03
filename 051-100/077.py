from functools import cache


@cache
def change_ways(coin_set: tuple[int], num: int) -> int:
    """returns the number of ways to partition a number into different sets 
    (same as change_ways function)"""
    if num == 0:  # 1 way to make change with 0 money (no coins)
        return 1
    elif num < 0:  # no ways to make change for less than 0 money
        return 0
    elif len(coin_set) == 0:  # no ways to make change with no choice of coins
        return 0
    # recursive formula given number of ways to give change with smaller 
    # set of change
    return (change_ways(coin_set[:-1], num) 
        + change_ways(coin_set, num-coin_set[-1]))


def isprime(num: int) -> bool:
    """returns True if num is prime"""
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(5, int(num ** 0.5)+3, 6):  # for 6k +- 1
        if num % i == 0 or num % (i+2) == 0:
            return False
    return True


def next_prime(num: int) -> int:
    """return the smallest prime larger than num"""
    while True:
        num += 2
        if isprime(num):
            return num


def main():
    # declare variables
    prime_list = [2, 3, 5, 7]
    current_number = 10
    number_of_ways = 5

    # main loop
    while number_of_ways <= 5000:
        current_number += 1

        # update prime list
        if current_number % 2 == 1 and isprime(current_number):
            prime_list.append(current_number)

        # calculate number of ways to write number as a sum of primes
        number_of_ways = change_ways(tuple(prime_list), current_number)

    # print result
    print(f"{current_number} can be written in {number_of_ways} ways")


if __name__ == "__main__":
    main()
