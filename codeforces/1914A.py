def problem1914A() -> int:
    _ = input()  # length of contest (in minutes)
    contest_log = input()
    problem_times = [0] * 26  # position 0 = problem A, 1 = B, ...
    
    for c in contest_log:
        pos = ord(c) - 65  # position in problem times array
        problem_times[pos] += 1

    solved = 0
    for problem, time in enumerate(problem_times):
        if time > problem:  # check if enough time to solve problem
            solved += 1

    return solved

test_cases = int(input())
for _ in range(test_cases):
    print(problem1914A())