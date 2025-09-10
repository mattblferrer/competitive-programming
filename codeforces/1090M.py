def problem1090M() -> int:
    n, k = map(int, input().split(' '))
    a = list(map(int, input().split(' ')))
    max_length = 1
    length = 1

    for x, y in zip(a, a[1:]):
        if x == y:
            length = 1
        else:
            length += 1
        max_length = max(max_length, length)

    return max_length

print(problem1090M())