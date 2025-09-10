def problem4A() -> None:
    weight = int(input())
    if weight % 2 == 0 and weight > 2:
        print("YES")
    else:
        print("NO")

problem4A()