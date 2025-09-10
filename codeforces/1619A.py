def problem1619A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        string = input()
        if string[:len(string) // 2] == string[len(string) // 2:]:
            print("YES")
        else:
            print("NO")

problem1619A()