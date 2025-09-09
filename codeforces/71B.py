from math import floor

def problem71B() -> list[int]:
    n, k, t = map(int, input().split(' '))
    a = [0] * n
    left = floor((t / 100) * (n * k))

    for i in range(n):
        a[i] += min(k, left)
        left -= k
        if left <= 0:
            return a

print(*problem71B())