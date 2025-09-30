def problem677A() -> int:
    _, h = map(int, input().split(" "))
    heights = list(map(int, input().split(" ")))
    min_width = 0  # minimum valid width of road

    for a_i in heights:
        if a_i > h:
            min_width += 2
        else:
            min_width += 1

    return min_width

print(problem677A())