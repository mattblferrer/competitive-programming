def problem440A() -> int:
    n = int(input())
    expected_sum = n * (n + 1) // 2
    sum_a = sum(map(int, input().split()))
    return expected_sum - sum_a

print(problem440A())