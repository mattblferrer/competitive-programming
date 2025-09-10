def problem30A() -> str:
    a, b, n = map(int, input().split())
    for x in range(-1000, 1001):
        if a * pow(x, n) == b:
            return str(x)

    return "No solution"

print(problem30A())