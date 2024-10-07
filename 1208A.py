def problem1208A() -> int:
    a, b, n = map(int, input().split(" "))
    if n % 3 == 0:
        return a
    if n % 3 == 1:
        return b
    if n % 3 == 2:
        return a ^ b


test_cases = int(input())
for _ in range(test_cases):
    print(problem1208A())