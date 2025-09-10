def problem29A() -> str:
    n = int(input())
    camels = set()

    for _ in range(n):
        x_i, d_i = map(int, input().split(' '))
        camels.add((x_i, d_i))

    for x_i, d_i in camels:
        if (x_i + d_i, -d_i) in camels:
            return "YES"
    return "NO"

print(problem29A())