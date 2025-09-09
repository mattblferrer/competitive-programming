def problem1873A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        s = input()
        if s in ["bca", "cab"]:
            print("NO")
        else:
            print("YES")

problem1873A()