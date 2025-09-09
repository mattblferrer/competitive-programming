def problem34A() -> tuple[int, int]:
    n = int(input())
    soldiers = list(map(int, input().split(' ')))
    min_diff = float('inf')
    min_i, min_j = 0, 0

    for i in range(n):
        j = (i + 1) % n  # next in circle
        diff = abs(soldiers[j] - soldiers[i])
        if min_diff > diff:
            min_i, min_j = i, j
            min_diff = diff

    return min_i + 1, min_j + 1  # since 1-based index

print(*problem34A())