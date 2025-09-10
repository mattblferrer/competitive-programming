def problem1371A() -> int:
    n = int(input())  # number of sticks
    return (n + 1) // 2  # can join (1, n), (2, n - 1), ...

test_cases = int(input())
for _ in range(test_cases):
    print(problem1371A())