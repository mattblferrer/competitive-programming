def problem1787A() -> None:
    n = int(input())
    for x in range(1, 20):
        for y in range(x, 20):
            if x**y * y + y**x * x == n:
                print(x, y)
                return

    else:
        print(-1)

test_cases = int(input())
for _ in range(test_cases):
    problem1787A()