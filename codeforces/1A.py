from math import ceil

def problem1A() -> int:
    n, m, a = map(int, input().split(' '))
    return ceil(n / a) * ceil(m / a)

print(problem1A())