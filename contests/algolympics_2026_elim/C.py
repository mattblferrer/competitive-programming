from collections import deque, defaultdict as dd
 
n = int(input())
grid = []
for _ in range(n):
    grid.append(list(input()))
 
start = (0, 0)
end = (0, 0)
 
adj = dd(list)
adj_portals = dd(list)
portals = dd(list)
 
for i in range(n):
    for j in range(n):
        if grid[i][j] == "#": continue
        if grid[i][j] == "@": start = (i, j)
        if grid[i][j] == "!": end = (i, j)
        if grid[i][j].isalpha(): portals[grid[i][j]].append((i, j))
        
        for dx, dy in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
            if not 0 <= i + dx < n: continue
            if not 0 <= j + dy < n: continue
 
            if grid[i + dx][j + dy] == "#": continue
            if abs(dx + dy) != 1: continue
            if grid[i + dx][j + dy] == grid[i][j] and grid[i][j].isalpha(): continue
 
            v = (i + dx, j + dy)
            if grid[i + dx][j + dy].isalpha():
                v = grid[i + dx][j + dy]
 
            if grid[i][j].isalpha():
                adj[grid[i][j]].append(v)
            else:
                adj[i, j].append(v)
 
visited = set()
q = deque()
q.append((start, 0))
ans = -1
while q:
    u, d = q.popleft()
    if u in visited: continue
    visited.add(u)
    if u == end:
        ans = d
        break
    for v in adj[u]:
        q.append((v, d + 1))
 
print(ans)