from math import ceil

def problem1032A() -> int:
    n, k = map(int, input().split(' '))
    a = list(map(int, input().split(' ')))
    counts = {}

    for a_i in a:
        if a_i not in counts:
            counts[a_i] = 1
        else:
            counts[a_i] += 1

    max_count = ceil(max(counts.values()) / k) * k
    min_stolen = 0 
    for count in counts.values():
        min_stolen += max_count - count

    return min_stolen

print(problem1032A())