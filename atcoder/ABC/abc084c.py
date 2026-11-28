def ABC084C() -> None:
    n = int(input())
    c = []
    s = []
    f = []

    for _ in range(n - 1):
        c_i, s_i, f_i = map(int, input().split())
        c.append(c_i)
        s.append(s_i)
        f.append(f_i)

    for i in range(n):  # starting station index
        time = 0
        for j in range(i, n - 1):  # current station index
            wait = time % f[j]
            if wait > 0:
                wait = f[j] - wait
            time = max(time + wait, s[j]) + c[j]
        print(time)

ABC084C()