def problem1624A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        _ = input()  # length of array a
        a = list(map(int, input().split(" ")))
        print(max(a) - min(a))

problem1624A()