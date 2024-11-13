def CSES1643() -> int:
    n = int(input())
    x = list(map(int, input().split()))
    curr_sum = 0
    max_sum = -float('inf')

    for x_i in x:
        curr_sum = max(x_i, curr_sum + x_i)
        max_sum = max(max_sum, curr_sum)

    return max_sum

print(CSES1643())