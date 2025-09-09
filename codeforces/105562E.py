N, K = map(int, input().split(' '))
S = input()

ans = ''
for i in range(N):
    ans += S[pow(2, K, N) * i % N]
print(ans)