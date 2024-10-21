def problem492B() -> float:
    n, l = map(int, input().split())
    a = sorted(map(int, input().split()))
    d = 0
    
    for left, right in zip(a, a[1:]):  # lanterns on street
        d = max(d, (right - left) / 2)
    d = max(d, a[0], l - a[-1])  # endpoints of street
        
    return d

print(problem492B())