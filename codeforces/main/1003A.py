def problem1003A() -> int:
    n = int(input())
    a = list(map(int, input().split(' ')))
    counts = {}

    for a_i in a:
        if a_i not in counts:
            counts[a_i] = 1
        else:
            counts[a_i] += 1

    return max(counts.values())

print(problem1003A())