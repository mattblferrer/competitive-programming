def problem1772A() -> None:
    test_cases = int(input())

    for _ in range(test_cases):
        a, b = map(int, input().split("+"))
        print(a + b)

if __name__ == "__main__":
    problem1772A()