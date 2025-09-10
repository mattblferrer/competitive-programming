def problem129A() -> int:
    n = int(input())
    a = list(map(int, input().split(' ')))
    total = sum(a)
    can_steal = 0

    for a_i in a:
        if a_i % 2 == total % 2:
            can_steal += 1

    return can_steal

print(problem129A())