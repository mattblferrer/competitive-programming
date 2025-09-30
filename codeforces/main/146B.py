def problem146B() -> int:
    def mask(n: int) -> int:
        num_mask = ""
        for digit in str(n):
            if digit in ["4", "7"]:
                num_mask += digit
        
        if num_mask:
            return int(num_mask)
        return 0

    a, b = map(int, input().split(' '))
    curr = max(a, b - 1)
    while True:
        curr += 1
        if mask(curr) == b:
            return curr

print(problem146B())