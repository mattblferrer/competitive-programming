def solve():
    n = int(input())
    A = list(map(int, input().split()))

    if len(set(A)) == 1:
        print(0)
        return
    
    ans, cur = 1, A[1] > A[0]
    for i in range(1, n - 1):
        if cur == 1 and A[i + 1] <= A[i]:
            ans += 1
            cur = 0
        elif cur == 0 and A[i + 1] >= A[i]:
            ans += 1
            cur = 1

    print(ans)

    return

solve()