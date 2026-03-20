from heapq import *
import sys
input = sys.stdin.readline

n,m = map(int,input().split())
inf = float('inf')
home,office = map(int,input().split())
home -= 1; office -= 1

elevations = list(map(int,input().split()))

graph = [[] for _ in range(n)]

for _ in range(m):
    u,v = map(int,input().split())
    u -= 1
    v -= 1
    graph[u].append(v)
    graph[v].append(u)

def dijkstra(source,target,graph):
    # dist = [[[inf]*3 for _ in range(5)] for _ in range(n)]
    dist = [inf for _ in range(15*n)]
    dist[source*15] = 0

    pq = [(0,source,0,0)] # dist,node,steps,last_change

    while pq:
        distance,node,steps,last_change = heappop(pq)
        elev1 = elevations[node]
        offset = node*15 + steps * 3 + last_change
        if distance > dist[offset]:
            continue
        
        for neighbor in graph[node]:
            elev2 = elevations[neighbor]

            if elev1 == elev2:
                change = last_change # retain the last elevation change
            elif elev1 > elev2:
                change = 1 # downwards
            else:
                change = 2 # upwards

            temp = distance + 1

            if steps < 4: # go forward
                offset2 = neighbor*15 + (steps+1)*3 + change
                if temp < dist[offset2]:
                    dist[offset2] = temp
                    heappush(pq,(temp,neighbor,steps+1,change))
            
            # take a break, can only do so when most recent elevation change is downwards
            if change == 1 and temp < dist[neighbor*15]:
                dist[neighbor*15] = temp
                heappush(pq,(temp,neighbor,0,0))
    
    return dist[target*15]

ans = dijkstra(home,office,graph)

if ans == inf:
    print("Johnny stays home")
else:
    print(ans)