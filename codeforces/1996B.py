def problem1996B() -> list[str]:
    n, k = map(int, input().split(' '))
    grid = [input() for _ in range(n)]
    new_grid = []
    for r in range(n // k):
        new_line = ""
        for c in range(n // k):
            new_line += grid[r * k][c * k]
        new_grid.append(new_line)

    return new_grid

test_cases = int(input())
for _ in range(test_cases):
    print(*problem1996B(), sep="\n")