def problem630L() -> int:
    n = input()
    new_n = int(n[0] + n[2] + n[4] + n[3] + n[1])
    return format(new_n ** 5 % 100_000, "05d")

print(problem630L())