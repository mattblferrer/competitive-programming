def problem630B() -> float:
    n, t = map(int, input().split(' '))
    return n * pow(1.000000011, t)

print(problem630B())