def problem415A() -> list[int]:
    n, m = map(int, input().split(' '))
    b = list(map(int, input().split(' ')))
    lights = [True] * n
    turned_off = [0] * n

    for b_i in b:
        for i in range(b_i - 1, n):
            if lights[i]:
                turned_off[i] = b_i
                lights[i] = False

    return turned_off

print(*problem415A())