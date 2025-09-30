def problem710A() -> int:
    square = input()
    c, d = square[0], int(square[1])
    if c in ['a', 'h'] and d in [1, 8]:  # corner
        return 3
    if c in ['a', 'h'] or d in [1, 8]:  # edge
        return 5
    return 8

print(problem710A())