from math import factorial

def problem630G() -> int:
    n = int(input())
    return factorial(n + 4) // (factorial(n - 1) * factorial(5)) * factorial(n + 2) // (factorial(n - 1) * factorial(3))

print(problem630G())