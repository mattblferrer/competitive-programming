def problem279B() -> int:
    n, t = map(int, input().split())
    a = list(map(int, input().split()))
    left, right = 0, 0
    curr_sum = 0
    max_books = 0

    while right < n:
        if curr_sum <= t:
            curr_sum += a[right]
            right += 1
        if curr_sum > t:
            curr_sum -= a[left]
            left += 1
        max_books = max(max_books, right - left)

    return max_books

print(problem279B())