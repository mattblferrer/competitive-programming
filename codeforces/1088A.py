def problem1088A() -> None:
    x = int(input())
    for b in range(1, x + 1):
        for a in range(b, x + 1, b):
            if a * b > x and a // b < x:
                print(a, b)
                return
    print(-1)

problem1088A()