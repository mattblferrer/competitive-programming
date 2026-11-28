def ABC096C() -> str:
    h, w = map(int, input().split(' '))
    grid = [['.'] * w]  # add upper border

    for _ in range(h):  # get input rows and convert to array grid
        row = ['.'] + list(input()) + ['.']
        grid.append(row)
    grid.append(['.'] * w)  # add lower border

    for row in range(1, h):
        for col in range(1, w):
            # check neighbors of cell (row, col)
            if grid[row][col] == ".":
                continue
            if grid[row][col - 1] == "#":  # left
                continue
            if grid[row][col + 1] == "#":  # right
                continue
            if grid[row - 1][col] == "#":  # up
                continue
            if grid[row + 1][col] == "#":  # down
                continue
            return "No"
        
    return "Yes"

print(ABC096C())