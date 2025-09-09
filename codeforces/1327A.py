def problem1327A() -> str:
    n, k = map(int, input().split(' '))
    if n < k * k:
        return "NO"
    if n % 2 == k % 2:
        return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1327A())