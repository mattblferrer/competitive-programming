def problem1692A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        distances = list(map(int, input().split(" ")))  # a, b, c, d
        front = 0  # number of participants in front of Timur

        for d in distances[1:]:
            if d > distances[0]:
                front += 1

        print(front)

problem1692A()