def problem510A() -> None:
    n, m = map(int, input().split(" "))
    for row in range(n):
        if row % 2 == 0:  # snake going horizontally
            print("#" * m)
        elif row % 4 == 1:  # snake going along right edge
            print("." * (m - 1) + "#")
        else:  # snake going along left edge
            print("#" + (m - 1) * ".")

problem510A()