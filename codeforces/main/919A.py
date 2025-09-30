def problem919A() -> float:
    n, m = map(int, input().split(' '))
    min_price = float('inf')

    for _ in range(n):
        a, b = map(int, input().split(' '))
        min_price = min(min_price, a / b)

    return min_price * m

print(problem919A())