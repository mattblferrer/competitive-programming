def problem1915B() -> str:
    for _ in range(3):
        row = input()
        row_mask = [0, 0, 0]  # "bitmask" of A, B, C appearances in row
        is_missing = False

        for letter in row:
            if letter == "?":
                is_missing = True
            else:
                row_mask[ord(letter) - 65] += 1

        if is_missing:
            missing = chr(row_mask.index(0) + 65)  # since A = 65 in ASCII

    return missing

test_cases = int(input())
for _ in range(test_cases):
    print(problem1915B())