def problem102B() -> int:
    n = input()
    moves = 0

    while True:
        if int(n) < 10:
            return moves
        n = str(sum(int(digit) for digit in n))
        moves += 1

    return moves

print(problem102B())