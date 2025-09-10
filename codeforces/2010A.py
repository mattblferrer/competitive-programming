def problem2010A() -> int:
    n = int(input())
    a = list(map(int, input().split()))
    alternating_sum = 0

    for i in range(n):
        if i % 2 == 0:
            alternating_sum += a[i]
        else:
            alternating_sum -= a[i]

    return alternating_sum

test_cases = int(input())
for _ in range(test_cases):
    print(problem2010A())