"""
CODE FOR TESTING:
grid = [
    [0, 0, 3, 0, 2, 0, 6, 0, 0],
    [9, 0, 0, 3, 0, 5, 0, 0, 1],
    [0, 0, 1, 8, 0, 6, 4, 0, 0],
    [0, 0, 8, 1, 0, 2, 9, 0, 0],
    [7, 0, 0, 0, 0, 0, 0, 0, 8],
    [0, 0, 6, 7, 0, 8, 2, 0, 0],
    [0, 0, 2, 6, 0, 9, 5, 0, 0],
    [8, 0, 0, 2, 0, 3, 0, 0, 9],
    [0, 0, 5, 0, 1, 0, 3, 0, 0]
]
"""
from copy import deepcopy


# returns the possibilities for each cell in the grid
def possibilities(grid):
    possibilities = [[[]]*9 for i in range(9)] # initialize 9x9 array
    all_nums = [i for i in range(1, 10)]

    # rows
    for row_num, row in enumerate(grid):
        row_poss = [i for i in row if i != 0]  # remove 0 from row
        row_poss = list(set(all_nums) - set(row_poss))  # inverse

        # assign row possibilities to cells in row
        for col_num, cell in enumerate(row):
            if cell == 0:
                possibilities[row_num][col_num] = row_poss

    # columns
    for col_num in range(9):
        col = [row[col_num] for row in grid]  # get column from left to right
        col_poss = [i for i in col if i != 0]  # remove 0 from column
        col_poss = list(set(all_nums) - set(col_poss))  # inverse

        # subtract column possibilities from row possibilities
        for row_num, cell in enumerate(row):
            if cell == 0:
                curr_poss = possibilities[row_num][col_num]  # current possibilities

                # take intersection
                possibilities[row_num][col_num] = [val for val in curr_poss if val in col_poss]

    # 3x3 squares
    for grid_r in range(3):  # grid row
        for grid_c in range(3):   # grid column
            square = []  # initialize 3x3 square array

            for row_num in range(grid_r*3, grid_r*3 + 3):  # 3 rows in 3x3 sqr
                col = [grid[row_num][i] for i in range(grid_c*3, grid_c*3 + 3)]
                square.extend(col)

            sqr_poss = [i for i in square if i != 0]  # remove 0 from square
            sqr_poss = list(set(all_nums) - set(sqr_poss))  # inverse

            # subtract square possibilities from current possibilities
            for row_num in range(grid_r*3, grid_r*3 + 3):  # 3 rows in 3x3 sqr
                for col_num in range(grid_c*3, grid_c*3 + 3):  # 3 cols in 3x3 sqr
                    if grid[row_num][col_num] == 0:
                        curr_poss = possibilities[row_num][col_num]  # current possibilities

                        # take intersection
                        possibilities[row_num][col_num] = [val for val in curr_poss if val in sqr_poss]

    return possibilities   


# fills in cells in the grid with only a single possibility
def one_poss_fill(grid, poss): 
    for row_num in range(9):
        for col_num in range(9):
            if len(poss[row_num][col_num]) == 1:
                grid[row_num][col_num] = poss[row_num][col_num][0]

    return grid


# returns True if a digit can be put in the grid cell with coords (x, y), False 
# otherwise
def is_possible(grid, digit, x, y):
    if grid[x][y] != 0:  # cell already occupied
        return False

    for i in range(9):  # check row and column
        if grid[y][i] == digit or grid[i][x] == digit:
            return False

    grid_r = y // 3  # row of 3x3 square
    grid_c = x // 3  # column of 3x3 square

    for i in range(3):  # check 3x3 square
        for j in range(3):
            if grid[grid_r*3+i][grid_c*3+j] == digit:
                return False

    return True


# solves a Sudoku using backtracking
def solve_bt(grid):
    # TODO
    pass


# read file
file1 = open('p096_sudoku.txt', 'r')
lines = file1.readlines()

# strip whitespace and read Sudoku grids
line_num = 0
grids = []

while line_num < len(lines):
    line = lines[line_num].strip()
    if line[0:4] == "Grid":  # check for grid number
        grid = []
        for i in range(1, 10):
            row = lines[line_num+i].strip()  # strip whitespace from rows
            row = [int(digit) for digit in row]  # convert to single digits
            grid.append(row)

        grids.append(grid)
        line_num += 10

# solve each grid
sum3digits = 0  # sum of 3 digit numbers in top left corner

for grid in grids:
    # eliminate "easy" cells
    while True:
        prevGrid = deepcopy(grid)  # previous iteration of grid
        grid = one_poss_fill(grid, possibilities(grid))

        if grid == prevGrid:  # if nothing changed
            break

    for row in grid:
        print(row)
    print("")
    # backtracking
    # TODO

# print result
print(sum3digits)
