n=  int(input())
arr = list(map(int,input().split()))

from math import gcd

g = arr[0]
for i in range(n):
    g = gcd(g, arr[i])

if g != 1:
    print(1)
    print(g, 1)
else:
    print(2)
    print(4, 2)
    print(2, 1)
