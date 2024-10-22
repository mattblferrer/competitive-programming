def problem2014B() -> str:
    n, k = map(int, input().split())
    if k % 4 == 0:
        return "YES"
    elif k % 4 == 1:
        if n % 2 == 0:
            return "YES"
        else:
            return "NO"
    elif k % 4 == 2:
        return "NO"
    elif k % 4 == 3:
        if n % 2 == 0:
            return "NO"
        else:
            return "YES"

test_cases = int(input())
for _ in range(test_cases):
    print(problem2014B())