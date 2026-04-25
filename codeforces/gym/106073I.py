n = int(input())
d = []
curr = tuple(map(int, input().split()))
for i in range(n - 1):
    x, y = map(int, input().split())
    d.append(abs(curr[0] - x) + abs(curr[1] - y))
    curr = (x, y)

k = d[0] - 1
valid = False
while not valid:
    valid = True
    over = 0
    curr = k
    for i in range(n - 1):
        if curr > d[i] - 1:
            valid = False
            over = curr - d[i] + 1
            break
        elif curr <= 0:
            valid = False
            over = -curr
            break
        curr = d[i] - curr
    if valid:
        break
    if k < 1:
        break
    k -= max(1, over)

if k <= 0:
    print(-1)
else:
    print(k)
    