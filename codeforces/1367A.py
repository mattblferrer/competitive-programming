def problem1367A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        b = input()
        print(b[0::2] + b[-1])

problem1367A()