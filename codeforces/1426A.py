def problem1426A() -> int:
    n, x = map(int, input().split(" "))
    if n <= 2:
        return 1
    return (n - 3) // x + 2

test_cases = int(input())
for _ in range(test_cases):
    print(problem1426A())