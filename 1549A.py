def problem1549A() -> None:
    p = int(input())
    for a in range(2, p):
        mod = p % a
        if p - mod != a:
            print(a, p - mod)
            break

test_cases = int(input())
for _ in range(test_cases):
    problem1549A()