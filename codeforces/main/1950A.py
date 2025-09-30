def problem1950A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        a, b, c = map(int, input().split(" "))
        if a < b < c:
            print("STAIR")
        elif a < b > c:
            print("PEAK")
        else:
            print("NONE")

problem1950A()