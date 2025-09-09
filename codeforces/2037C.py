def problem2037C() -> list[int]:
    n = int(input())
    if n < 5:
        return [-1]
    return [1, 3] + list(range(7, n + 1, 2))+ [5, 4, 2] + list(range(6, n + 1, 2))

test_cases = int(input())
for _ in range(test_cases):
    print(*problem2037C())