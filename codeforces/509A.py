def problem509A() -> int:
    n = int(input())
    previous_row = [1] * n  # define first row
    current_row = [1] * n  # define current row

    for _ in range(n - 1):
        current_row = []
        left = 0  # value to the left of current
        for i in range(n):
            current_row.append(left + previous_row[i])
            left = current_row[-1]

        previous_row = current_row

    return current_row[-1]  # last value always maximum

print(problem509A())