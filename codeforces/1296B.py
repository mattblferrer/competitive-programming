def problem1296B() -> int:
    n = int(input())
    max_burles = 0

    while n >= 10:
        max_burles += 10 ** (len(str(n)) - 1)
        n -= 10 ** (len(str(n)) - 1) - 10 ** (len(str(n)) - 2)

    return max_burles + n

test_cases = int(input())
for _ in range(test_cases):
    print(problem1296B())