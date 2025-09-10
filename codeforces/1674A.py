def problem1674A() -> tuple[int, int]:
    x, y = map(int, input().split(' '))
    if y % x != 0:
        return 0, 0
    return 1, y // x

test_cases = int(input())
for _ in range(test_cases):
    print(*problem1674A())