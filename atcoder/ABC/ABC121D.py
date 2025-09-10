def ABC121D() -> int:
    def xor_sum(n: int) -> int:
        result = [n, 1, n + 1, 0]
        return result[n % 4]
    
    a, b = map(int, input().split())
    return xor_sum(b) ^ xor_sum(a - 1)

print(ABC121D())