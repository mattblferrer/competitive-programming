def problem540A() -> int:
    _ = input()  # number of digits in lock code
    original = input()
    password = input()
    moves = 0

    for a, b in zip(original, password):
        a, b = int(a), int(b)
        moves += min(abs(b - a), min(a, b) - max(a, b) + 10)

    return moves

print(problem540A())