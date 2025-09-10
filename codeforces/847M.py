def problem847M() -> int:
    n = int(input())
    t = list(map(int, input().split(' ')))
    diff = t[1] - t[0]
    for curr, next in zip(t, t[1:]):
        if next - curr != diff:
            return t[-1]
    return t[-1] + diff

print(problem847M())