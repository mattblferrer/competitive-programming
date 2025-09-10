from math import lcm

def problem235A() -> int:
    n = int(input())
    if n in [1, 2, 3]:
        return [1, 2, 6][n - 1]
    if n % 2 == 1:
        return n * (n - 1) * (n - 2)
    elif n % 3 != 0:
        return n * (n - 1) * (n - 3)
    else:
        return (n - 1) * (n - 2) * (n - 3)

print(problem235A())