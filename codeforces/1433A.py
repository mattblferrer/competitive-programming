def problem1433A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        x = input()  # apartment number as string
        print((int(x[0]) - 1) * 10 + len(x) * (len(x) + 1) // 2)

problem1433A()