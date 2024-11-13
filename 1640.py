def CSES1640() -> str:
    n, x = map(int, input().split())
    a = sorted((a_i, i) for i, a_i in enumerate(map(int, input().split())
                                                ,start=1))
    left, right = 0, n - 1

    while left < right:
        if a[left][0] + a[right][0] > x:
            right -= 1
        elif a[left][0] + a[right][0] < x:
            left += 1
        else:
            return f"{a[left][1]} {a[right][1]}"
        
    return "IMPOSSIBLE"

print(CSES1640())