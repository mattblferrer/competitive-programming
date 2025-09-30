def problem2014B() -> str:
    n, k = map(int, input().split())
    leaves = (n * (n + 1)) // 2 - ((n - k) * (n - k + 1)) // 2

    if leaves % 2 == 0:
        return "YES"
    return "NO"
    
test_cases = int(input())
for _ in range(test_cases):
    print(problem2014B())