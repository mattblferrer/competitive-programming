def problem165A() -> int:
    n = int(input())
    x_coords = {}  # x: [list of y coordinates] pairs
    y_coords = {}  # y: [list of x coordinates] pairs
    points = []
    supercentrals = 0

    for _ in range(n):
        x, y = map(int, input().split(' '))
        points.append((x, y))

        if x not in x_coords:
            x_coords[x] = [y]
        else:
            x_coords[x].append(y)
        if y not in y_coords:
            y_coords[y] = [x]
        else:
            y_coords[y].append(x)

    for x, y in points:  # check each point if supercentral
        xp_list = y_coords.get(y, [y])
        if min(xp_list) >= x:  # left neighbor
            continue
        if max(xp_list) <= x:  # right neighbor
            continue

        yp_list = x_coords.get(x, [x])
        if min(yp_list) >= y:  # lower neighbor
            continue
        if max(yp_list) <= y:  # upper neighbor
            continue

        supercentrals += 1

    return supercentrals

print(problem165A())