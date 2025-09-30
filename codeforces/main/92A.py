def problem92A() -> int:
    n, m = map(int, input().split(' '))
    m %= (n * (n + 1) // 2)  # go around circle until last loop

    for i in range(1, n + 1):
        if m < i:
            return m
        m -= i

print(problem92A())