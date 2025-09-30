def problem577A() -> int:
    n, x = map(int, input().split(' '))
    factors = 0

    for i in range(1, n + 1):
        if x % i == 0 and x // i <= n:
            factors += 1

    return factors

print(problem577A())