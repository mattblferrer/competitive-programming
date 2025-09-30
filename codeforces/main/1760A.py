def problem1760A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        _, b, _ = sorted(tuple(map(int, input().split(" "))))
        print(b)

if __name__ == "__main__":
    problem1760A()