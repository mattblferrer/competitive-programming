def problem2031B() -> str:
    n = int(input())
    p = list(map(int, input().split(' ')))

    for i in range(n - 1):
        if p[i] == p[i + 1] + 1:
            p[i], p[i + 1] = p[i + 1], p[i]
                
    if p == list(range(1, n + 1)):
        return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem2031B())