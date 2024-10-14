def problem102697040() -> str:
    # get input sudoku as 9x9 array
    sudoku = []
    for _ in range(9):
        row = list(map(int, input().split(' ')))
        seen = [False] * 9

        # check if no number appears in same row twice
        for n in row:  
            if seen[n - 1]:
                return "INVALID"
            seen[n - 1] = True
        sudoku.append(row)

    # check if no number appears in same column twice
    for col in range(9):
        seen = [False] * 9
        for row in range(9):
            if seen[sudoku[row][col] - 1]:
                return "INVALID"
            seen[sudoku[row][col] - 1] = True

    # check if no number appears in same 3x3 square twice
    for square_row in range(3):  # row of 3x3 square in grid
        for square_col in range(3):  # column of 3x3 square in grid
            seen = [False] * 9

            for in_row in range(3):  # row inside square
                for in_col in range(3):  # column inside square
                    row = square_row * 3 + in_row
                    col = square_col * 3 + in_col
                    
                    if seen[sudoku[row][col] - 1]:
                        return "INVALID"
                    seen[sudoku[row][col] - 1] = True
            
    return "VALID"
    

print(problem102697040())