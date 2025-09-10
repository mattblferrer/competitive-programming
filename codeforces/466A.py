def problem466A() -> int:
    n, m, a, b = map(int, input().split(' '))
    if b / m < a:  # better to buy the special ticket 
        return b * (n // m) + min(b, a * (n % m))
    else:  # better to buy the single ticket
        return a * n

print(problem466A())