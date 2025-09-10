def problem479A() -> int:
    a = int(input())
    b = int(input())
    c = int(input())

    return max(
        a + b + c,
        a + b * c, 
        a * b + c,
        (a + b) * c,
        a * (b + c),
        a * b * c
    )

print(problem479A())