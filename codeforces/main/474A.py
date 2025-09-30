def problem474A() -> str:
    shifting = input()
    shifted = input()
    original = ""
    rows = ['qwertyuiop', 'asdfghjkl;', 'zxcvbnm,./']

    for char in shifted:
        for i, row in enumerate(rows):
            if char not in row:
                continue
            row_number = i
            row_index = row.index(char)
            break

        if shifting == 'L':  # shift back to the right
            original += rows[row_number][row_index + 1]
        else:  # shift back to the left
            original += rows[row_number][row_index - 1]
        
    return original

print(problem474A())