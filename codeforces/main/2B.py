def count_factor(x, f):
    ans = 0
    if x == 0:
        return 1_000_000  # large number to avoid using zeros in normal DP
    while x % f == 0:
        x //= f
        ans += 1
    return ans

INF = 10**9
n = int(input())
grid = [list(map(int, input().split())) for _ in range(n)]

cnt2 = [[count_factor(x, 2) for x in row] for row in grid]
cnt5 = [[count_factor(x, 5) for x in row] for row in grid]
dp2 = [[INF] * n for _ in range(n)]
dp5 = [[INF] * n for _ in range(n)]
path2 = [[''] * n for _ in range(n)]
path5 = [[''] * n for _ in range(n)]
dp2[0][0] = cnt2[0][0]
dp5[0][0] = cnt5[0][0]

for i in range(n):
    for j in range(n):
        if i == j == 0:
            continue
        if i > 0 and dp2[i - 1][j] + cnt2[i][j] < dp2[i][j]:
            dp2[i][j] = dp2[i - 1][j] + cnt2[i][j]
            path2[i][j] = 'D'
        if j > 0 and dp2[i][j - 1] + cnt2[i][j] < dp2[i][j]:
            dp2[i][j] = dp2[i][j - 1] + cnt2[i][j]
            path2[i][j] = 'R'
        if i > 0 and dp5[i - 1][j] + cnt5[i][j] < dp5[i][j]:
            dp5[i][j] = dp5[i - 1][j] + cnt5[i][j]
            path5[i][j] = 'D'
        if j > 0 and dp5[i][j - 1] + cnt5[i][j] < dp5[i][j]:
            dp5[i][j] = dp5[i][j - 1] + cnt5[i][j]
            path5[i][j] = 'R'

res2 = dp2[-1][-1]
res5 = dp5[-1][-1]
ans = min(res2, res5)
use_path = path2 if res2 < res5 else path5

# find zero
zero_pos = None
for i in range(n):
    for j in range(n):
        if grid[i][j] == 0:
            zero_pos = (i, j)

# if zero gives better path (1 zero < ans)
if zero_pos and ans > 1:
    zx, zy = zero_pos
    path = 'D' * zx + 'R' * zy + 'D' * (n - zx - 1) + 'R' * (n - zy - 1)
    print(1)
    print(path)
else:
    # normal reconstruction
    i, j = n - 1, n - 1
    path = []
    while i > 0 or j > 0:
        if use_path[i][j] == 'D':
            i -= 1
            path.append('D')
        else:
            j -= 1
            path.append('R')
    print(ans)
    print(''.join(path[::-1]))
