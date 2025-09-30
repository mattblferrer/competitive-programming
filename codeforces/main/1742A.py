def problem1742A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        a, b, c = sorted(tuple(map(int, input().split(" "))))
        if a + b == c:
            print("YES")
        else:
            print("NO")

if __name__ == "__main__":
    problem1742A()