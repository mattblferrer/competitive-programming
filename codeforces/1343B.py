def problem1343B() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        n = int(input())  # length of balanced array
        if n % 4 != 0:
            print("NO")
        else:
            print("YES")
            for i in range(2, n + 1, 2):  # print even half of array
                print(i, end=" ")

            for i in range(1, n - 1, 2):  # print odd half of array
                print(i, end=" ")

            print(n - 1 + n // 2)

problem1343B()