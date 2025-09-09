def problem245A() -> list[str, str]:
    n = int(input())
    x_a, y_a, x_b, y_b = 0, 0, 0, 0

    for _ in range(n):
        t_i, x_i, y_i = map(int, input().split(' '))
        if t_i == 1:  # server a
            x_a += x_i
            y_a += y_i
        else:  # server b
            x_b += x_i
            y_b += y_i

    status = []
    if x_a >= y_a:
        status.append("LIVE")
    else:
        status.append("DEAD")
    if x_b >= y_b:
        status.append("LIVE")
    else:
        status.append("DEAD")
    return status

print(*problem245A(), sep="\n")