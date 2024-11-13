def CSES1640() -> str:
    n, x = map(int, input().split())
    a = list(map(int, input().split()))
    sorted_a = sorted(a)

    for i, a_i in enumerate(sorted_a):
        if a_i >= x:
            return "IMPOSSIBLE"
        
        left, right = -1, n
        while right - left > 1:
            mid = (left + right) // 2
            if x - a_i < sorted_a[mid]:
                right = mid
            else:
                left = mid
                
        n_1, n_2 = a_i, sorted_a[left]
        if i == left:
            continue
        if n_1 + n_2 != x:
            continue
        
        return f"{a.index(n_1) + 1} {n - a[::-1].index(n_2)}"
        
    return "IMPOSSIBLE"

print(CSES1640())