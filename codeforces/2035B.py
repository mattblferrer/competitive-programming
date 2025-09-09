def problem2035B() -> int:
    n = int(input())
    if n in [1, 3]:
        return -1
    if n % 2 == 0:
        return int("3" * (n - 2) + "66")
    else:
        return int("3" * (n - 4) + "6366")

test_cases = int(input())
for _ in range(test_cases):
    print(problem2035B())