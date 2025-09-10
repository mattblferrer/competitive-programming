def ABC205D() -> None:
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    diff_a = [a[0] - 1] + [y - x - 1 for x, y in zip(a, a[1:])]
    
    pref_a = []
    pref = 0
    for d_i in diff_a:
        pref += d_i
        pref_a.append(pref)

    for _ in range(q):
        q_i = int(input()) - 1
        left, right = -1, n
        while right - left > 1:
            mid = (left + right) // 2
            if pref_a[mid] > q_i:
                right = mid
            else:
                left = mid

        print(q_i + right + 1)

ABC205D()
