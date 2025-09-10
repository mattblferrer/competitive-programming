from math import ceil

def problem11A() -> int:
    n, d = map(int, input().split(' '))
    b = list(map(int, input().split(' ')))
    moves = 0

    for i in range(1, n):
        if b[i] <= b[i - 1]:
            current_move = ceil((b[i - 1] - b[i] + 1) / d)
            moves += current_move
            b[i] += d * current_move

    return moves

print(problem11A())