def problem996A() -> int:
    n = int(input())
    bills = [100, 20, 10, 5, 1]
    min_bills = 0  # minimum number of bills Allen could receive

    for bill in bills:
        min_bills += n // bill
        n %= bill

    return min_bills

print(problem996A())