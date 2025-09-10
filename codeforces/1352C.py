def problem1352C() -> int:
    n, k = map(int, input().split(' '))
    return k + (k - 1) // (n - 1)

test_cases = int(input())
for _ in range(test_cases):
    print(problem1352C())