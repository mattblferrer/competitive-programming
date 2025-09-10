def problem327A() -> int:
    n = int(input())
    a = list(map(int, input().split()))

    max_sum_change = -float('inf')
    for i in range(n):
        for j in range(i, n):
            sum_change = sum(1 if a[k] == 0 else -1 for k in range(i, j + 1))
            max_sum_change = max(max_sum_change, sum_change)

    return sum(a) + max_sum_change
            
print(problem327A())