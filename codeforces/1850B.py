def problem1850B() -> int:
    n = int(input())
    best_responses = []

    for i in range(n):
        a_i, b_i = map(int, input().split(' '))
        if a_i <= 10:
            best_responses.append((b_i, a_i, i))

    return max(best_responses)[2] + 1  # since 1-based index

test_cases = int(input())
for _ in range(test_cases):
    print(problem1850B())