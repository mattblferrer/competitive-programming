def problem214A() -> int:
    n, m = map(int, input().split(" "))
    result = 0

    for a in range(32):
        for b in range(32):
            if a*a + b == n and a + b*b == m:
                result += 1
            
    return result

print(problem214A())