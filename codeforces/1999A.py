def problem1999A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        n = int(input())
        print(n // 10 + n % 10)

if __name__ == "__main__":
    problem1999A()