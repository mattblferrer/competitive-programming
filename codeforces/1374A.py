def problem1374A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        x, y, n = map(int, input().split(" "))
        if n % x >= y:
            print(n - (n % x - y))
        else:
            print(n - (n % x - y) - x)

problem1374A()