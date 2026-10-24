n = int(input())
from collections import defaultdict

artists = defaultdict(int)
top = [[] for _ in range(10)]
for _ in range(n):
    s = input().split()
    # print(s)
    
    for i in range(10):
        x = s[i]
        artists[x] += 1
        top[i].append(x)
    # for x in s:
        # artists[x] += 1
best = 0
curr = None


for x in artists:
    if artists[x] > best:
        best = artists[x]
        curr = [x]
    elif artists[x] == best:
        curr.append(x)

if len(curr) == 1:
    print(curr[0])
else:
    idx = 0
    # print(top)
    while idx < 10:
        score = 0
        best = []
        for x in curr:
            temp = top[idx].count(x)
            if temp > score:
                best = [x]
                score = temp
            elif temp == score:
                best.append(x)
        
        if len(best) != 1:
            idx += 1
            curr = best
        else:
            print(best[0])
            # print(best, idx)
            exit()
        
    print("tie")