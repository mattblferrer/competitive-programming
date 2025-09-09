def problem155A() -> int:
    _ = input()  # number of contests coder joined
    points = list(map(int, input().split(" ")))
    maximum = points[0]
    minimum = points[0]
    amazing = 0  # number of amazing performances

    for p in points:
        if p > maximum:  # new maximum points
            maximum = p
            amazing += 1
        elif p < minimum:  # new minimum points
            minimum = p
            amazing += 1

    return amazing

print(problem155A())