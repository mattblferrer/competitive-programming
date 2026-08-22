def solve():
    a, b, c = list(map(int, input().split()))

    A = [(a, 0), (b, 1), (c, 2)]
    A.sort()
    
    if A[0][0] + A[1][0] < A[2][0]:
        print('No')
        return
    
    if A[0][0] == 0 and A[1][0] == 0 and A[2][0] == 0:
        print('Yes\na\na\na')
        return
    
    s, t, u = '', '', ''
    if A[1][1] + A[2][1] == 1:
        # print(1)
        s = 'a' * (A[0][0] + A[1][0] - A[2][0]) + 'b' * A[1][0]
        t = 'a' * (A[0][0] + A[1][0])
        u = 'a' * A[1][0]
        if A[2][1] == 1:
            t, u = u, t
    elif A[1][1] + A[2][1] == 2:
        # print(2)
        t = 'a' * (A[0][0] + A[1][0] - A[2][0]) + 'b' * A[1][0]
        s = 'a' * (A[0][0] + A[1][0]) 
        u = 'a' * A[1][0]
        if A[2][1] == 2:
            s, u = u, s   
    elif A[1][1] + A[2][1] == 3:
        # print(3)
        u = 'a' * (A[0][0] + A[1][0] - A[2][0]) + 'b' * A[1][0]
        s = 'a' * (A[0][0] + A[1][0])
        t = 'a' * A[1][0]
        if A[2][1] == 2:
            s, t = t, s
            
    print('Yes')
    print(s)
    print(t)
    print(u)

    return

solve()