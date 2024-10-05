def problem1506A() -> int:
    n, m, x = map(int, input().split(" "))
    row, column = (x - 1) % n, (x - 1) // n  # row, column of x "by columns"
    return row * m + column + 1  # since 1-indexed

test_cases = int(input())
for _ in range(test_cases):
    print(problem1506A())