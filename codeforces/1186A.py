def problem1186A() -> str:
    n, m, k = map(int, input().split(" "))
    if n > m or n > k:
        return "NO"
    return "YES"

print(problem1186A())