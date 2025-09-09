def problem41A() -> None:
    s = input()
    t = input()
    if s[::-1] == t:
        print("YES")
    else:
        print("NO")

problem41A()