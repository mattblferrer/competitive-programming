n = int(input())
base = ['A', 'b', 'c', 'd', '1', '!']
chars = [chr(i) for i in range(33, 127)]

ans = []
pairs = []
for i in range(0, 93, 2):
    pairs.append([chars[i], chars[i + 1]])

ptr = 0
while len(ans) < n:
    curr = base.copy()
    curr += pairs[ptr % 47]
    curr += pairs[ptr // 47]
    ans.append(curr)
    ptr += 1

for password in ans:
    print(''.join(password))