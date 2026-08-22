n = int(input())

A, B, C = sorted(list(map(int, input().split())))
for i in range(n - 1):
    a, b, c = sorted(list(map(int, input().split())))
    A = min(A, a)
    B = min(B, b)
    C = min(C, c)
    
print(A * B * C)