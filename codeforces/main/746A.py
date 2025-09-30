def problem746A() -> int:
    a = int(input())
    b = int(input())
    c = int(input())

    minimum = min(a, b / 2, c / 4)
    if minimum == a:
        return a * 7
    if minimum == b / 2:
        return b // 2 * 7
    if minimum == c / 4:
        return c // 4 * 7

print(problem746A())