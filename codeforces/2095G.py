from math import pi

n, k = map(int, input().split())
coords = []
for _ in range(n):
    x, y = map(int, input().split())
    coords.append((x, y))

coords.sort()
line_dist = [0]
for (c1, c2) in zip(coords, coords[1:]):
    dist = (abs(c1[0] - c2[0]) ** 2 + abs(c1[1] - c2[1]) ** 2) ** 0.5
    line_dist.append(line_dist[-1] + dist)

min_diff = float('inf')
for (c1, c2) in zip(line_dist, line_dist[k - 1:]):
    min_diff = min(min_diff, c2 - c1)
    
print((min_diff / 2) ** 2 * pi)