def problem1553A() -> int:
    n = int(input())
    return (n + 1) // 10

test_cases = int(input())
for _ in range(test_cases):
    print(problem1553A())