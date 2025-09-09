def problem1980A() -> int:
    _, m = map(int, input().split(" "))
    difficulties = input()
    diff_counts = [0] * 7

    for d in difficulties:  # get counts of difficulties from A to G
        position = ord(d) - 65  # position in diff_counts array (A = 0, ...)
        diff_counts[position] += 1    

    problems_needed = 0
    for d in diff_counts:
        problems_needed += max(0, m - d)
    
    return problems_needed

test_cases = int(input())
for _ in range(test_cases):
    print(problem1980A())