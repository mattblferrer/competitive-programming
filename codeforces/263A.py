def problem263A() -> int:
    matrix = []
    for _ in range(5):  # get matrix rows as input
        matrix.append(input().split(" "))
    
    for r in range(5):  # find position of 1
        for c in range(5):
            if matrix[r][c] == "1":
                r1, c1 = r, c  # position of 1 found
                break

    return abs(r1 - 2) + abs(c1 - 2)  # since center is 2, 2 (0-indexed)

print(problem263A())