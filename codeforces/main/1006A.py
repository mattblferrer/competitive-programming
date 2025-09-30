def problem1006A() -> list[int]:
    n = int(input())
    a = list(map(int, input().split(' ')))
    new_a = []

    for a_i in a:
        if a_i % 2 == 1:
            new_a.append(a_i)
        else:
            new_a.append(a_i - 1)

    return new_a

print(*problem1006A())