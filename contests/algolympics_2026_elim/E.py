from collections import deque
from heapq import *
import sys
 
input = sys.stdin.readline
 
n,m = map(int,input().split())
 
graph = [[] for _ in range(n)]
 
for i in range(m):
    u,v = map(int,input().split())
    u -= 1
    v -= 1
    graph[u].append(v)
    graph[v].append(u)
 
a,b,h = map(int,input().split())
 
a -= 1
b -= 1
h -= 1
 
def bfs(source,graph):
    distances = [0] * len(graph)
 
    queue = deque([source])
    visited = set([source])
 
    while queue:
        node = queue.popleft()
 
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                distances[neighbor] = distances[node] + 1
                queue.append(neighbor)
    
    return distances
 
distances = bfs(h,graph)
# print(distances)
 
def dijkstra(source,target,graph,distances):
    # we want to maximize the score, ie the minimum distance of h, to the nodes of the path from a to b.
    
    dist = [-float('inf')] * n 
    # dist[x] = score of path from src to x
    dist[source] = distances[source]
    parent = [None] * n
    pq = [(-dist[source],source)] # maxheap
 
    while pq:
        curr, node = heappop(pq)
        curr *= -1
 
        if curr < dist[node]:
            continue
 
        for neighbor in graph[node]:
            temp = min(curr,distances[neighbor])
            if temp > dist[neighbor]:
                dist[neighbor] = temp
                parent[neighbor] = node
                heappush(pq,(-temp,neighbor))
    
    return dist[target]
 
ans = dijkstra(a,b,graph,distances)
 
 
print(ans)