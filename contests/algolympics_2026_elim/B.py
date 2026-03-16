import sys
sys.setrecursionlimit(20000)
input = sys.stdin.readline
 
n = int(input())
k1, k2, k = map(lambda x: int(x) - 1, input().split())
 
adj = [list() for _ in range(n)]
 
for i in range(n):
    t, *adj[i] = list(map(lambda x: int(x) - 1, input().split()))
 
memo = dict()
ans = 0
def inorder(x):
    global ans, memo, adj
    if x in memo: return memo[x]
    if x == k: return True
    ans += 1
    for child in adj[x]:
        if inorder(child):
            memo[x] = True
            return True
    memo[x] = False
    return False
 
if inorder(k1) and inorder(k2):
    print(ans)
else:
    print("IMPOSSIBLE")