def problem1422A() -> int:
    a, b, c = map(int, input().split(" "))
    return a + b + c - 1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1422A())