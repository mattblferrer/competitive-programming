def problem1351C() -> int:
    moves = input()
    x, y = 0, 0
    prev_x, prev_y = 0, 0
    paths = set()
    time = 0

    for m in moves:
        if m == 'N':
            y += 1
        elif m == 'S':
            y -= 1
        elif m == 'E':
            x += 1
        elif m == 'W':
            x -= 1
        if (prev_x, prev_y, x, y) in paths or (x, y, prev_x, prev_y) in paths:
            time += 1
        else:
            time += 5

        paths.add((prev_x, prev_y, x, y))
        paths.add((x, y, prev_x, prev_y))
        prev_x, prev_y = x, y

    return time

test_cases = int(input())
for _ in range(test_cases):
    print(problem1351C())