def problem1915A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        a, b, c = map(int, input().split(" "))
        print(a ^ b ^ c)

problem1915A()