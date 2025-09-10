def problem1646A() -> int:
    n, s = map(int, input().split(' '))
    return s // n ** 2

test_cases = int(input())
for _ in range(test_cases):
    print(problem1646A())