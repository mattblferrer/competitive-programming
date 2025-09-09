def problem1054A() -> str:
    x, y, z, t_1, t_2, t_3 = map(int, input().split(' '))
    stairs = t_1 * abs(x - y)
    elevator = t_3 * 3 + t_2 * (abs(x - z) + abs(x - y))

    if stairs < elevator:
        return "NO"
    return "YES"

print(problem1054A())