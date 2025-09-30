def problem1971A() -> None:
    a, b = map(int, input().split(" "))
    if a > b:
        print(b, a)
    else:
        print(a, b)

test_cases = int(input())
for _ in range(test_cases):
    problem1971A()