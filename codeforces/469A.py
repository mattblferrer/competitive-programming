def problem469A() -> str:
    n = int(input())  # number of levels
    x_levels = list(map(int, input().split(" ")))
    y_levels = list(map(int, input().split(" ")))
    x_set = set(x_levels[1:])
    y_set = set(y_levels[1:])

    if len(x_set | y_set) == n:
        return "I become the guy."
    return "Oh, my keyboard!"

print(problem469A()) 