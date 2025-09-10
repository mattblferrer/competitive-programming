def problem36B() -> None:
    def drawFractal(row: int, col: int, k: int) -> None:
        if k == 0:
            new_matrix[row][col] = "."
            return
        
        for i in range(n):  # recursively draw smaller fractals or black squares
            for j in range(n):
                new_row = row + i * n ** (k - 1)
                new_col = col + j * n ** (k - 1)

                if original_matrix[i][j] == ".":  # draw smaller fractal
                    drawFractal(new_row, new_col, k - 1)
                else:  # draw smaller black square
                    drawBlack(new_row, new_col, k - 1)
        
    def drawBlack(row: int, col: int, k: int) -> None:
        for i in range(n ** k):
            for j in range(n ** k):
                new_matrix[row + i][col + j] = "*"

    # read original matrix from file
    with open("input.txt", 'r') as file:
        n, k = map(int, file.readline().split(' '))
        original_matrix = []
        for _ in range(n):  
            original_matrix.append(file.readline().strip())

        # modify new matrix
        new_matrix = [[0] * (n ** k) for _ in range(n ** k)]
        drawFractal(0, 0, k)

    # write new matrix to output file
    with open("output.txt", 'w+') as file:
        for row in new_matrix:
            file.write("".join(row) + "\n")

problem36B()