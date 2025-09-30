def problem1985A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        a, b = input().split(" ")
        print(b[0] + a[1:], a[0] + b[1:])

problem1985A()