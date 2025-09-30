def problem1778A() -> int:
    n = int(input())
    a = list(map(int, input().split()))
    best = 2
    
    for curr, next in zip(a, a[1:]):
        best = min(best, curr + next)
    return sum(a) - 2 * best

test_cases = int(input())
for _ in range(test_cases):
    print(problem1778A())