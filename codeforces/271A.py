def problem271A() -> int:
    y = int(input()) + 1  # the next year number to start checking
    while True:
        unique_digits = len(set(str(y)))
        if unique_digits == 4:
            return y
        y += 1

print(problem271A())