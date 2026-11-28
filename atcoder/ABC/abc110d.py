from math import comb

def ABC110D() -> int:
    n, m = map(int, input().split())
    mod = pow(10, 9) + 7
    pf = {}
    for i in range(2, int(m ** 0.5) + 1):
        while m % i == 0:
            if i not in pf:
                pf[i] = 0
            pf[i] += 1
            m //= i
    if m != 1:
        pf[m] = 1
    ans = 1
    for b in pf:
        p = pf[b]
        ans = (ans * comb(p + n - 1, p)) % mod
    return ans

print(ABC110D())