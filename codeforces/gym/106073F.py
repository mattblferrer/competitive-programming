from collections import deque, defaultdict as dd
MOD = 10 ** 9 + 7
n, q = map(int, input().split())
tables = [0] * n
order = list(map(lambda x: int(x) - 1, input().split()))

def inverse(x):
    return pow(x, MOD - 2, MOD)

scaled = []
mult = 1
for i in range(q):
    mult *= inverse(2)
    mult %= MOD
    scaled.append((mult * (order[i] + 1)) % MOD)

pfix_right = [0]
for i in range(q):
    pfix_right.append((pfix_right[-1] + scaled[i]) % MOD)

pfix_left = deque([0])
for i in range(q - 1, -1 ,-1):
    pfix_left.appendleft((pfix_left[0] + scaled[i]) % MOD)
pfix_left = list(pfix_left)

idx = dd(list)
for i in range(q):
    idx[order[i]].append(i)


for i in range(n):
    for index in idx[i]:
        #print(index, ((pfix_right[-1] - pfix_right[index + 1]) * pow(2, index, MOD)) % MOD)
        tables[i] += (pfix_right[-1] - pfix_right[index + 1]) * pow(2, index, MOD)
        tables[i] %= MOD
tables[0] += pfix_right[-1]
tables[0] %= MOD

for i in range(n):
    print(tables[i] % MOD)