def ABC085B() -> int:
    n = int(input())
    d = set(int(input()) for _ in range(n))
    return len(d)

print(ABC085B())