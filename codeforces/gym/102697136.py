n = int(input())
r, t = 0, 0
for _ in range(n):
    rc, tc = map(int, input().split("/"))
    r, t = r + rc, t + tc
print(str(r) + "/" + str(t))