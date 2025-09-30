def problem584A() -> int:
    n, t = map(int, input().split(' '))
    result = 10 ** (n - 1)  # length n
    limit = 10 ** n  # length (n + 1)

    while result < limit:
        if result % t == 0:
            return result
        result += 1

    return -1

print(problem584A())