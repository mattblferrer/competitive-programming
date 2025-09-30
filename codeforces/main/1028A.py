def problem1028A() -> tuple[int, int]:
    n, m = map(int, input().split(' '))
    for i in range(n):
        row = input()
        start = -1
        end = -1

        for j, square in enumerate(row):
            if start == -1 and square == "B":  # first B in row
                start = j
            if start > -1 and square == "W":  # first W after B in row
                end = j - 1
                break

        if start > -1 and end == -1:  # if row ended on B
            end = m - 1
        if start > -1:  # if B seen in row, +1 because 1-based index
            return i + (end - start) // 2 + 1, (start + end) // 2 + 1

print(*problem1028A())