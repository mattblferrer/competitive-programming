def problem743B() -> int:
    _, k = map(int, input().split(' '))
    result = 1
    while k % 2 == 0:
        k //= 2
        result += 1

    return result

print(problem743B())