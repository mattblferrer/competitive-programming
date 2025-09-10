def problem27A() -> int:
    n = int(input())
    a = sorted(map(int, input().split(' ')))

    for i, a_i in enumerate(a, start=1):
        if a_i != i:
            return i
    return n + 1

print(problem27A())