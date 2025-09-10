def problem707A() -> str:
    n, _ = map(int, input().split(" "))
    for _ in range(n):
        row = input().split(" ")
        for color in row:
            if color not in ['B', 'G', 'W']:
                return "#Color"

    return "#Black&White"

print(problem707A())