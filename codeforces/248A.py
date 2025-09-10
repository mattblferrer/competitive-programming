def problem248A() -> int:
    n = int(input())
    left_sum, right_sum = 0, 0

    for _ in range(n):
        left, right = map(int, input().split(' '))
        left_sum += left
        right_sum += right

    return min(left_sum, n - left_sum) + min(right_sum, n - right_sum)

print(problem248A())