def problem913A() -> int:
    n = int(input())
    m = int(input())
    if n > 30:  # m mod 2^n where n > 30 = m
        return m
    return m % (1 << n)

print(problem913A())