def problem1722A() -> None:
    test_cases = int(input())
    test = sorted("Timur")

    for _ in range(test_cases):
        _ = input()  # length of string
        string = input()
        if sorted(string) == test:
            print("YES")
        else:
            print("NO")

problem1722A()