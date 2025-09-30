def problem1787A() -> None:
    n = int(input())
    if n % 2 == 0:  # trivial solution: 1^(n/2) * (n/2) + (n/2)^1 * 1 == n
        print(1, n // 2)
    else:
        print(-1)

test_cases = int(input())
for _ in range(test_cases):
    problem1787A()