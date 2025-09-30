def problem1351A() -> int:
    a, b = map(int, input().split(" "))
    return a + b

test_cases = int(input())
for _ in range(test_cases):
    print(problem1351A())