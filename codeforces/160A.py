def problem160A() -> int:
    _ = input()  # number of coins
    coins = sorted(list(map(int, input().split(' '))), reverse=True)
    twin_1 = 0
    twin_2 = sum(coins)
    coins_taken = 0

    while twin_1 <= twin_2:
        twin_1 += coins[coins_taken]
        twin_2 -= coins[coins_taken]
        coins_taken += 1

    return coins_taken

print(problem160A())