def problem344A() -> int:
    magnets = int(input())
    previous = ""
    groups = 0

    for _ in range(magnets):
        m = input()  # current magnet
        if m != previous:
            groups += 1
        previous = m

    return groups

print(problem344A())