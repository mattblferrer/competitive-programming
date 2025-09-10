def problem16A() -> str:
    n, _ = map(int, input().split(" "))

    for row_num in range(n):
        row = input()
        for a, b in zip(row, row[1:]):  # check adjacent colors in row
            if a != b:
                return "NO"
        if row_num == 0:  # don't check previous row if first row
            prev_row_num = row[0]
            continue
        if prev_row_num == row[0]:  # check if previous row matches current
            return "NO"
        prev_row_num = row[0]

    return "YES"

print(problem16A())