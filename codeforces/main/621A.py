def problem621A() -> int:
    _ = input()
    arr = list(map(int, input().split(" ")))
    odds = 0
    total_sum = 0
    min_odd = float('inf')

    for n in arr:
        if n % 2 == 1:  # odd
            min_odd = min(min_odd, n)
            odds += 1
        total_sum += n

    if odds % 2 == 1:  # total sum not divisible by 2
        return total_sum - min_odd
    return total_sum

print(problem621A())