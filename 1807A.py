def problem1807A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        a, b, c = map(int, input().split(" "))
        if a + b == c:
            print("+")
        else:
            print("-")

if __name__ == "__main__":
    problem1807A()