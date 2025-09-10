def problem546A() -> int:
    k, n, w = map(int, input().split(" "))
    total_cost = k * w * (w + 1) // 2  
    return max(0, total_cost - n)

print(problem546A())