def problem768B() -> int:
    def ones(n: int, l: int, r: int) -> int:
        if n == 1:
            return 1
            
        mid = 2 ** (n.bit_length() - 1) - 1
        if l < mid:
            if r < mid:
                return ones(n // 2, l, r)
            elif r == mid:
                return ones(n // 2, l, mid - 1) + n % 2
            else:
                return ones(n // 2, l, mid - 1) + n % 2 + ones(n // 2, 0, r - mid - 1)
        elif l == mid:
            if r == mid:
                return n % 2
            else:
                return n % 2 + ones(n // 2, 0, r - mid - 1)
        else:
            return ones(n // 2, l - mid - 1, r - mid - 1)
        
    n, l, r = map(int, input().split())
    return ones(n, l - 1, r - 1)

print(problem768B())