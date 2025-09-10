def problem1987A() -> int:
    n, k = map(int, input().split(' '))
    return (n - 1) * k + 1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1987A())