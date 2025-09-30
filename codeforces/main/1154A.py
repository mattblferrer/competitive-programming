def problem1154A() -> None:
    values = sorted(list(map(int, input().split(" "))))  # a <= b <= c
    c = values[3] - values[0]  # (a + b + c) - (a + b)
    a = values[1] - c  # (a + c) - c
    b = values[3] - a - c  # (a + b + c) - a - c

    print(a, b, c)
 
problem1154A()