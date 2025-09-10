def problem38B() -> int:
    rook = input()
    knight = input()

    # convert rook and knight to coordinates
    ra, rb = ord(rook[0]) - 96, int(rook[1])
    ka, kb = ord(knight[0]) - 96, int(knight[1])

    # generate set of all squares on chessboard
    squares = set()
    for i in range(1, 9):
        for j in range(1, 9):
            squares.add((i, j))

    # remove squares of rook
    for i in range(1, 9):  
        if (i, rb) in squares:
            squares.remove((i, rb))
    for j in range(1, 9):  
        if (ra, j) in squares:
            squares.remove((ra, j))

    # remove squares of knight, and squares of knight move away from rook
    squares.remove((ka, kb))
    for i in [1, -1]:
        for j in [2, -2]:
            # knight
            if (ka + i, kb + j) in squares:
                squares.remove((ka + i, kb + j))
            if (ka + j, kb + i) in squares:
                squares.remove((ka + j, kb + i))

            # rook
            if (ra + i, rb + j) in squares:
                squares.remove((ra + i, rb + j))
            if (ra + j, rb + i) in squares:
                squares.remove((ra + j, rb + i))

    return len(squares)

print(problem38B())