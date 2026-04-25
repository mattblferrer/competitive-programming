n, k = map(int, input().split())
a = list(map(int, input().split()))
 
min_idx = 0
for i in range(n):
    if a[i] < a[min_idx]:
        min_idx = i
 
l = a[min_idx] - 1
r = a[min_idx] + k + 1
ans = float('inf')
while r - l > 1:
    m = (r + l) // 2
    curr_k = k
    #print(m)
    curr = a.copy()
    #print(f"needs {m - a[min_idx]}, so can start {curr_k - (m - a[min_idx])} after")
    for i in range(min(n - 1, min_idx + curr_k - (m - a[min_idx])), -1, -1):
        if curr_k < 1: break
        curr[i] += curr_k
        curr_k -= 1
    #print(curr)
    if min(curr) >= m:
        l = m
    else:
        r = m
 
print(l)