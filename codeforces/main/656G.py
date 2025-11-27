f, it, t = map(int, input().split())
g = []
for _ in range(f):
    line = input()
    g.append(line)
ans = 0
for i in range(it):
    curr = 0
    for j in range(f):
        if g[j][i] == 'Y':
            curr += 1
    if curr >= t:
        ans += 1
# kitten
print(ans)