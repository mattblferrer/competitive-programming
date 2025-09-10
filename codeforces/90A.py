from math import ceil

def problem90A() -> int:
    r, g, b = map(int, input().split())
    return max(ceil(r / 2) * 3 - 3, ceil(g / 2) * 3 - 2, ceil(b / 2) * 3 - 1) + 30

print(problem90A())