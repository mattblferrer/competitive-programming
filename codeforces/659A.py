def problem659A() -> int:
    n, a, b = map(int, input().split(' '))
    return (a + b - 1) % n + 1

print(problem659A())