def problem935A() -> int:
    n = int(input())
    ways = 0

    for l in range(1, n // 2 + 1):
        if (n - l) % l == 0:
            ways += 1

    return ways

print(problem935A())