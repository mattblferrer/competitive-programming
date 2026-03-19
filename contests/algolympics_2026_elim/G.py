n = int(input())
arr1 = list(input().split())
arr2 = list(input().split())
 
from collections import defaultdict, deque
 
a = defaultdict(int)
for x in arr1:
    a[x] += 1
 
b = defaultdict(int)
for x in arr2:
    b[x] += 1
 
r = {"D":"H","H":"B","B":"D"}
c = {"M":"W","W":"A","A":"M"}
 
def defeats(card):
    race,class_ = card[0],card[1]
    return [race+c[class_],r[race]+class_,r[race]+c[class_]] # TW, WT, WW
 
graph = defaultdict(list)
capacity = defaultdict(dict)
 
# attach B to its cards, capacity is how many cards there are
for card in b:
    graph['source'].append('2'+card)
    graph['2'+card].append('source')
 
    capacity['source']['2'+card] = b[card]
    capacity['2'+card]['source'] = 0
 
# attach cards to A
for card in a:
    graph['1'+card].append('sink')
    graph['sink'].append('1'+card)
    
    capacity['1'+card]['sink'] = a[card]
    capacity['sink']['1'+card] = 0
 
# attach B's cards only to those it can defeat, then the cap will just be min(|A|,|B|)
for card2 in b:
    defeated = defeats(card2)
    for card1 in defeated:
        if card1 in a:
            graph['2'+card2].append('1'+card1)
            graph['1'+card1].append('2'+card2)
 
            capacity['2'+card2]['1'+card1] = min(a[card1],b[card2])
            capacity['1'+card1]['2'+card2] = 0
 
def bfs(source,target,graph,capacity):
    parent = dict( (x,-1) for x in graph)
    parent[source] = source
    queue = deque([(source,float('inf'))])
 
    while queue:
        curr, flow = queue.popleft()
 
        for next in graph[curr]:
            if parent[next] == -1 and capacity[curr][next] > 0:
                parent[next] = curr
                nf = min(flow,capacity[curr][next])
 
                if next == target:
                    return nf, parent
                
                queue.append((next,nf))
 
    return 0, parent
 
def maxflow(source, target, graph, capacity):
    flow = 0
 
    while True:
        nf, parent = bfs(source, target, graph, capacity)
        if nf == 0:
            break
 
        flow += nf
        curr = target
 
        while curr != source:
            prev = parent[curr]
            capacity[prev][curr] -= nf
            capacity[curr][prev] += nf
            curr = prev
 
    return flow
 
print(maxflow('source','sink',graph,capacity))