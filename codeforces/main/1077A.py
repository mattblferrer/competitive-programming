def problem1077A() -> int:
    a, b, k = map(int, input().split(' '))
    position = (k // 2) * (a - b)
    if k % 2 == 1:
        return position + a
    return position

test_cases = int(input())
for _ in range(test_cases):
    print(problem1077A())