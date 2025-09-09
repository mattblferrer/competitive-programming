def problem2031C() -> None:
    n = int(input())
    if n % 2 == 0:
        print(*[(i + 2) // 2 for i in range(n)])
    elif n < 27:
        print(-1)
    else:
        result = [1]
        result.extend([i // 2 for i in range(6, 14)])
        result.extend([1, 2])
        result.extend([i // 2 for i in range(14, 28)])
        result.extend([1, 2])
        result.extend([i // 2 for i in range(28, n + 1)])
        print(*result)

test_cases = int(input())
for _ in range(test_cases):
    problem2031C()