n, m = map(int, input().split())
ans = 0
a = [0] * m
for _ in range(n):
    b = list(map(int, input().split()))
    for i in range(m):
        a[i] = max(a[i], b[i])
print(sum(a))