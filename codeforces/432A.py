def problem432A() -> int:
    n, k = map(int, input().split(" "))
    y = list(map(int, input().split(" ")))
    available = 0  # number of contestants available

    for y_i in y:
        if y_i <= 5 - k:
            available += 1

    return available // 3

print(problem432A())