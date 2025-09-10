def problem1294A() -> str:
    a, b, c, n = map(int, input().split(' '))
    coin_sum = a + b + c + n
    if coin_sum % 3 != 0:
        return "NO"
    if max(a, b, c) > coin_sum // 3:
        return "NO"
    return "YES"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1294A())
