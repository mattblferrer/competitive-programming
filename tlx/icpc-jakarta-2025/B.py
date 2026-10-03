n = int(input())

arr = list(map(int,input().split()))

lowest_burning = []
for i in range(n):
    if arr[i] == 0:
        lowest_burning.append(0)
        continue 
    if i == 0 or i == n-1:
        lowest_burning.append(1)
    else:
        x = min(arr[i],arr[i-1]+1,arr[i+1]+1)
        lowest_burning.append(x)

left_pass = []
INF = float('inf')
for i in range(n):
    if arr[i] == 0:
        left_pass.append(INF)
        continue

    if i == 0:
        left_pass.append(lowest_burning[0])
    else:
        x = min(left_pass[-1]+1,lowest_burning[i])
        left_pass.append(x)

right_pass = []

for i in range(n-1,-1,-1):
    if arr[i] == 0:
        right_pass.append(INF)
        continue 

    if i == n-1:
        right_pass.append(lowest_burning[i])
    else:
        x = min(right_pass[-1]+1,lowest_burning[i])
        right_pass.append(x)

ans = []

right_pass = right_pass[::-1]

for i in range(n):
    ans.append(min(left_pass[i],right_pass[i]))

out = 0

for i in range(n):
    if ans[i] == INF:
        continue

    out = max(out,ans[i])

print(out)