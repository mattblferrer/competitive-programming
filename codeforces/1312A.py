def problem1312A() -> str:
    n, m = map(int, input().split(" "))
    if n % m == 0:
        return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1312A())