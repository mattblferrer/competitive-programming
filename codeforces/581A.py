def problem581A() -> None:
    a, b = map(int, input().split(" "))
    print(min(a, b), (max(a, b) - min(a, b)) // 2)

problem581A()