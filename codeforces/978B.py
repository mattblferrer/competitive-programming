def problem978B() -> str:
    _ = input()  # length of filename
    filename = input()
    consecutive = 0  # counts consecutive x's
    maximum = 0
    remove = 0  # x's to remove

    for char in filename:
        if char == "x":
            consecutive += 1
            maximum = max(maximum, consecutive)
            if consecutive >= 3:
                remove += 1
        else:
            consecutive = 0

    return remove

print(problem978B())