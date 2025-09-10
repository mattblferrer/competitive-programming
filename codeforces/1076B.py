def problem1076B() -> int:
    n = int(input())
    if n % 2 == 0:  # even
        return n // 2
    for i in range(3, int(n ** 0.5) + 1, 2):
        if n % i == 0:
            return (n - i) // 2 + 1
    return 1

print(problem1076B())