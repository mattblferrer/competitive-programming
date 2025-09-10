def problem1283A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        hh, mm = map(int, input().split(" "))
        print(1440 - hh * 60 - mm)

problem1283A()