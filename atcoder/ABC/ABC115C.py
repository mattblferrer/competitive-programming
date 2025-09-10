def ABC115C() -> int:
    n, k = map(int, input().split())
    h = sorted([int(input()) for _ in range(n)])
    min_diff = float('inf')

    for i in range(n - k + 1):
        min_diff = min(min_diff, h[i + k - 1] - h[i])

    return min_diff

print(ABC115C())