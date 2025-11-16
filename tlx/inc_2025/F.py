from math import gcd

s = input()
if '.' not in s:
    denom = 1
    num = int(s)
else:
    first, second = s.split('.')
    denom = 10**len(str(second))
    num = int(first) * denom + int(second)
frac = num / denom
l, r = map(int, input().split(' '))
if frac < l or frac > r:
    print(-1)
else:
    g = gcd(num, denom)
    num //= g
    denom //= g

    print(denom)
    w = num // denom
    f = num - (w * denom)
    a = [w for _ in range(denom)]
    for i in range(f):
        a[i] += 1
    for i in range(denom):
        print(a[i], end=" ")