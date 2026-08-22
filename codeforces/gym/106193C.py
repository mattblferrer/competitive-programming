def solve():
    n = int(input())

    if n == 0:
        print(0)
        return

    A = []
    while n > 0:
        A.append(n & 127)
        n >>= 7
    A = A[::-1]
    for i in range(0, len(A) - 1):
        A[i] += 128

    print(*A)
    return
    
solve()