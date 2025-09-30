def problem1977A() -> str:
    n, m = map(int, input().split(" "))
    if n % 2 == m % 2 and n >= m:  # only possible if n and m same parity
        return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1977A())