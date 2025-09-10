from functools import cache


@cache
# returns the number of ways to make change for a certain amount of money
def change_ways(coin_set: tuple[int], num: int) -> int:
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


# given variables
denominations = (1, 2, 5, 10, 20, 50, 100, 200)
ways = change_ways(denominations, 200)

# print result
print(f"The number of ways to make change for 2 pounds is {ways}")