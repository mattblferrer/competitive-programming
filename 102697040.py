def problem102697040() -> str:
    def valid_rows() -> bool:
        # check if no number appears in same row twice
        for row in range(9):
            seen = [False] * 9
            for col in range(9):  
                if seen[sudoku[row][col] - 1]:
                    return False
                seen[sudoku[row][col] - 1] = True
        return True

    def valid_columns() -> bool:
        # check if no number appears in same column twice
        for col in range(9):
            seen = [False] * 9
            for row in range(9):
                if seen[sudoku[row][col] - 1]:
                    return False
                seen[sudoku[row][col] - 1] = True
        return True

    def valid_boxes() -> bool:
        # check if no number appears in same 3x3 square twice
        for square_row in range(3):  # row of 3x3 square in grid
            for square_col in range(3):  # column of 3x3 square in grid
                seen = [False] * 9

                for in_row in range(3):  # row inside square
                    for in_col in range(3):  # column inside square
                        row = square_row * 3 + in_row
                        col = square_col * 3 + in_col
                        
                        if seen[sudoku[row][col] - 1]:
                            return False
                        seen[sudoku[row][col] - 1] = True
        return True

    # get input sudoku as 9x9 array
    sudoku = []
    for _ in range(9):
        row = list(map(int, input().split(' ')))
        sudoku.append(row)

    if valid_rows() and valid_columns and valid_boxes():
        return "VALID"
    return "INVALID"

print(problem102697040())