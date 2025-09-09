def problem174A() -> None:
    n, b = map(int, input().split(' '))
    a = list(map(int, input().split(' ')))
    total_drink = sum(a) + b
    drink_per_mug = total_drink / n

    if drink_per_mug < max(a):
        print(-1)
        return
    for a_i in a:
        print(format(drink_per_mug - a_i, ".6f"))

problem174A()