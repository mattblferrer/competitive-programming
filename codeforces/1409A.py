def problem1409A() -> int:
    a, b = map(int, input().split(" "))
    diff = abs(b - a)
    if diff % 10 == 0:
        return diff // 10
    return diff // 10 + 1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1409A())