def problem1475B() -> str:
    n = int(input())
    if (n % 2020) <= n // 2020:
        return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1475B())