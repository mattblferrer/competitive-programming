def problem34B() -> int:
    n, m = map(int, input().split(' '))
    a = sorted(map(int, input().split(' ')))
    return -sum(min(price, 0) for price in a[:m])

print(problem34B())