def problem1360A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        a, b = map(int, input().split(" "))
        print(max(max(a, b), (min(a, b) * 2)) ** 2)

problem1360A()