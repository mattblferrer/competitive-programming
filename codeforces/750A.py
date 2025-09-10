def problem750A() -> int:
    n, k = map(int, input().split(" "))
    minutes = 240 - k
    problems = 0

    while True:
        minutes -= (problems + 1) * 5
        if minutes < 0:
            break
        problems += 1

    return min(problems, n)

print(problem750A())