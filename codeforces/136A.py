def problem136A() -> None:
    _ = input()
    friends = list(map(int, input().split(" ")))
    gifts = {}

    for i, f in enumerate(friends):
        gifts[f] = i + 1

    for i in range(1, len(friends) + 1):
        print(gifts[i], end=" ")

problem136A()