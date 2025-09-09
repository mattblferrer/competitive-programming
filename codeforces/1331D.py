def problem1331D() -> int:
    hex = input()
    return int(hex[-1]) % 2

print(problem1331D())