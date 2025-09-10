def ABC115B() -> int:
    n = int(input())
    sum_p = 0
    max_p = 0
    
    for _ in range(n):
        p_i = int(input())
        sum_p += p_i
        max_p = max(p_i, max_p)

    return sum_p - (max_p // 2)  # subtract discount

print(ABC115B())