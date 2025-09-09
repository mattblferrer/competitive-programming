def problem774C() -> str:
    n = int(input())
    if n % 2 == 0:
        return "1" * (n // 2)
    else:
        return "7" + "1" * (n // 2 - 1)

print(problem774C())