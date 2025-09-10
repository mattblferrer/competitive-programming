def problem32A() -> int:
    n, d = map(int, input().split(' '))
    a = list(map(int, input().split(' ')))
    pairs = 0

    for i in range(n):
        for j in range(i + 1, n):
            if abs(a[i] - a[j]) <= d:
                pairs += 2  # pair (i, j), pair (j, i)

    return pairs

print(problem32A())