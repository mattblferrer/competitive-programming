def problem1993A() -> int:
    n = int(input())
    answers = input()
    answer_counts = {"A": 0, "B": 0, "C": 0, "D": 0}
    
    for answer in answers:
        if answer == "?":  # skip answer
            continue
        answer_counts[answer] += 1

    points = 0
    for count in answer_counts.values():
        points += min(n, count)

    return points

test_cases = int(input())
for _ in range(test_cases):
    print(problem1993A())