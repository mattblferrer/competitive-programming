def problem1703B() -> int:
    _ = input()  # length of contest string
    problems = input()
    solved = set()
    balloons = 0

    for p in problems:
        if p in solved:
            balloons += 1
        else:
            balloons += 2
        solved.add(p)

    return balloons

test_cases = int(input())
for _ in range(test_cases):
    print(problem1703B())