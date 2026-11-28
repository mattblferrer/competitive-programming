def ABC085C() -> list[int]:
    n, y = map(int, input().split())
    bills = [0, 0, 0]
    values = [10_000, 5_000, 1_000]
    for i in range(3):
        bills[i] += y // values[i]
        y %= values[i]

    if sum(bills) > n:  # not enough bills, impossible
        return [-1, -1, -1]
    while sum(bills) < n:
        if bills[1] and sum(bills) <= n - 4:  # split 5,000 into 5 1,000s
            bills[1] -= 1
            bills[2] += 5
        elif bills[0]:  # split 10,000 into 2 5,000s
            bills[0] -= 1
            bills[1] += 2     
        elif bills[1]:
            bills[1] -= 1
            bills[2] += 5
        else:
            return [-1, -1, -1]

    if sum(bills) == n:
        return bills
    return [-1, -1, -1]

print(*ABC085C())