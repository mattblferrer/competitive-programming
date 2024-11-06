def problem6B() -> int:
    n, m, c = input().split()
    n, m = int(n), int(m)
    office = [input() for _ in range(n)]
    adjacent = set()

    for row in range(n):
        for col in range(m):
            if office[row][col] == c:
                if row != 0 and office[row - 1][col] not in [".", c]:
                    adjacent.add(office[row - 1][col])  # up
                if row != n - 1 and office[row + 1][col] not in [".", c]:
                    adjacent.add(office[row + 1][col])  # down
                if col != 0 and office[row][col - 1] not in [".", c]:
                    adjacent.add(office[row][col - 1])  # left
                if col != m - 1 and office[row][col + 1] not in [".", c]:
                    adjacent.add(office[row][col + 1])  # right

    return len(adjacent)

print(problem6B())