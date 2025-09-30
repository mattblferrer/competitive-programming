def problem1692C() -> tuple[int, int]:
    empty_line = input()
    board = []
    for _ in range(8):
        row = input()
        board.append(row)

    for r in range(1, 8):
        for c in range(1, 8):
            if (board[r][c] == '#' and board[r-1][c-1] == '#' 
                and board[r-1][c+1] == '#'):
                return r + 1, c + 1

test_cases = int(input())
for _ in range(test_cases):
    print(*problem1692C())