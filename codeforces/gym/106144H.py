def solve():
    lm, rm = list(map(int, input().split()))
    lb, rb = list(map(int, input().split()))
    
    M = rm - lm
    B = (rb - lb + 1) // 2
    
    l, r = 0, min(M, B) + 1
    while r - l > 1:
        md = (l + r) // 2
        
        if 5 * md - 3 <= 2 * (lm + rm - 2 * lb):
            l = md
        else:
            r = md
    
    print(l)    
    
    return

t = int(input())
for _ in range(t):
    solve()