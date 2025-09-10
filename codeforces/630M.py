def problem630M() -> int:
    n = int(input()) % 360
    if n <= 45 or n >= 315:
        return 0
    elif 45 < n <= 135:
        return 1
    elif 135 < n <= 225:
        return 2
    else:
        return 3

print(problem630M())