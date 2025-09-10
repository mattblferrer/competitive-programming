def problem114A() -> None:
    k = int(input())
    l = int(input())

    importance = -1
    while l > 1:
        if l % k != 0:
            print("NO")
            return
        l //= k
        importance += 1

    print("YES")
    print(importance)

problem114A()