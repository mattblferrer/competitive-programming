from math import factorial

def problem630H() -> int:
    n = int(input())
    return factorial(n) ** 2 // (factorial(5) * factorial(n - 5) ** 2)

print(problem630H())