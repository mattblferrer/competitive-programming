def problem1703A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        string = input()
        if string.lower() == "yes":
            print("YES")
        else:
            print("NO")

problem1703A()