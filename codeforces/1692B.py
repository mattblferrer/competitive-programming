def problem1692B() -> int:
    n = int(input())
    a = list(map(int, input().split()))
    unique = set(a)
    if len(unique) % 2 == len(a) % 2:
        return len(unique)
    return len(unique) - 1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1692B())