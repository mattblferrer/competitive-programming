from math import gcd
h, w = map(int, input().split())
g = []
for i in range(h):
    g.append(list(input()))

m = g[0].count("#")
for i in range(h):
    m = gcd(m, g[0].count("#"))
for i in range(w):
    count = 0
    for j in range(h):
        if g[j][i] == "#":
            count +=1
    m = gcd(m, count)

for length in range(m, 1, -1):
    visited = set()
    possible = True
    for i in range(h):
        for j in range(w):
            if g[i][j] == ".": continue
            if (i, j) in visited: continue
            for x in range(length):
                for y in range(length):
                    if (i + x, j + y) in visited or i + x >= h or j + y >= w or g[i + x][j + y] == ".":
                        possible = False
                        break
                    visited.add((i + x, j + y))
                if not possible: break
            if not possible: break
        if not possible: break
    else:
        print(length)
        break
else:
    print(1)