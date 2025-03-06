def ABC117C() -> int:
    n, m = map(int, input().split())
    x = sorted(map(int, input().split()))
    diff = sorted(b - a for a, b in zip(x, x[1:]))
    if n == 1:
        return sum(diff)
    return sum(diff[:-n + 1])

print(ABC117C())