def problem1085A() -> str:
    t = input()
    s = ""

    for i in range(len(t)):
        if i % 2 != len(t) % 2:  # add left of t to left of s
            s = t[i // 2] + s
        else:  # add right of t to left of s
            s = t[-(i // 2) - 1] + s

    return s

print(problem1085A())