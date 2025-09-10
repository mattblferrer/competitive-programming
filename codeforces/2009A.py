def problem2009A() -> int:
    a, b = map(int, input().split(" "))
    return b - a

test_cases = int(input())
for _ in range(test_cases):
    print(problem2009A())