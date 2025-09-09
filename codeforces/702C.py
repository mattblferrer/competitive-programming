def problem702C() -> int:
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    a_p, b_p = 0, 0
    r = 0
    while a_p < n and b_p < m:
        if b[b_p] < a[a_p]:
            b_p += 1
        else:
            if b_p == 0:
                r = max(r, abs(a[a_p] - b[b_p]))
            else:
                r = max(r, min(abs(a[a_p] - b[b_p]), abs(a[a_p] - b[b_p - 1])))
            a_p += 1

    while a_p < n:
        r = max(r, abs(a[a_p] - b[-1]))
        a_p += 1
    
    return r
    
print(problem702C())