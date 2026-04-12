n, m = map(int, input().split())
adj = [list() for i in range(n)]
for i in range(m):
    u, v = map(lambda x: int(x) - 1, input().split())
    adj[u].append(v)
a, b = map(lambda x: int(x) - 1, input().split())

visited_a = set()
s = [a]
while s:
    curr = s.pop()
    if curr in visited_a: continue
    visited_a.add(curr)
    for v in adj[curr]:
        s.append(v)

visited_b = set()
s = [b]
while s:
    curr = s.pop()
    if curr in visited_a:
        print("yes")
        print(curr + 1)
        break
    if curr in visited_b: continue
    visited_b.add(curr)
    for v in adj[curr]:
        s.append(v)
else:
    print("no")