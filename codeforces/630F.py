from math import comb

def problem630F() -> int:
    n = int(input())
    return sum(comb(n, i) for i in range(5, 8))

print(problem630F())