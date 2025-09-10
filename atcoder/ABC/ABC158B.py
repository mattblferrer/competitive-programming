def ABC158B() -> int:
    n, a, b = map(int, input().split())
    return n // (a + b) * a + min(a, n % (a + b))

print(ABC158B())