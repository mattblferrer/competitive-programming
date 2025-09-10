def problem1955A() -> int:
    n, a, b = map(int, input().split(" "))
    if b > 2 * a:
        return n * a
    return (n // 2) * b + (n % 2) * a

test_cases = int(input())
for _ in range(test_cases):
    print(problem1955A())