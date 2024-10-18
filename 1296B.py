def problem1296B() -> int:
    n = int(input())
    if n < 10:
        return n

    max_burles = 0
    for i in range(len(str(n)) - 1, 0, -1):
        max_burles += n + (n % (10 ** i) + n // 10) % (10 ** i)
        n //= 10

    return max_burles

test_cases = int(input())
for _ in range(test_cases):
    print(problem1296B())