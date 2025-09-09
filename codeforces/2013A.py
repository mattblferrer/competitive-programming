from math import ceil

def problem2013A() -> int:
    n = int(input())
    x, y = map(int, input().split(' '))
    return ceil(n / min(x, y))

test_cases = int(input())
for _ in range(test_cases):
    print(problem2013A())