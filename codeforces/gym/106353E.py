from math import factorial

def choose(n, k):
    return factorial(n) / (factorial(k) * factorial(n - k))

def solve():
    n = int(input())
    s = input()
    cnt = [0, 0, 0]
    for c in s:
        if (c == 'r'):
            cnt[0] += 1
        elif (c == 'g'):
            cnt[1] += 1
        elif (c == 'b'):
            cnt[2] += 1
    
    cnt.sort()
    ans = 1.5 * cnt[0]
    for i in range(cnt[0] + 1):
        a = cnt[2] + i
        b = n - a
        ans += min(a, b) * 3.0 * choose(cnt[0], i) / (2 ** cnt[0])
    print(ans)
    
solve()