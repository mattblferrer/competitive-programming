def problem337A() -> int:
    n, _ = map(int, input().split(' '))
    puzzles = sorted(map(int, input().split(' ')))
    least_difference = float('inf')

    for i in range(len(puzzles) - n + 1):
        difference = puzzles[i + n - 1] - puzzles[i]
        least_difference = min(difference, least_difference)

    return least_difference

print(problem337A())