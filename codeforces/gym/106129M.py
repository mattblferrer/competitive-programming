from collections import defaultdict as dd
n, d = map(int, input().split())
p = list(map(int, input().split()))

def mex(l, r):
    s = set(range(r - l))
    for i in range(l, r):
        if p[i] in s:
            s.remove(p[i])
    for i in range(r - l):
        if i in s:
            return i
    return r - l
ans = mex(0, n)

indices = dd(list)
for i in range(n):
    indices[p[i]].append(i)

for i in range(ans):
    prev_min_index = indices[i][0]
    prev_l = max(0, prev_min_index - d + 1)
    prev_r = prev_l + d
    prev_end = prev_r + d
    #print(f"trying {i}")
    first = True
    for index in indices[i]:
        if first:
            first = False
            continue
        #print(f"index {index}")
        #print(prev_l, prev_r, prev_end)
        if prev_l <= index < prev_r: continue
        if index < prev_min_index + d:
            prev_r = index + 1
            prev_l = prev_r - d
            prev_end = prev_r + d
            continue
        if prev_r <= index < prev_end: break
        prev_min_index = index
        prev_l = max(prev_end, index - d + 1)
        prev_r = prev_l + d
        prev_end = prev_r + d
    else:
        print(i)
        break
else:
    print(ans)
