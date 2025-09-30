def problem486A() -> int:
    n = int(input())
    if n % 2 == 0:  # even, f(n) = positive
        return n // 2
    else:  # odd, f(n) = negative
        return -(n + 1) // 2

print(problem486A())