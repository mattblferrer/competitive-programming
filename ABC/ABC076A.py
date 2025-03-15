def ABC076A() -> int:
    r = int(input())
    g = int(input())
    return r + (g - r) * 2

print(ABC076A())