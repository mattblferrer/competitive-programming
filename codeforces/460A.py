def problem460A() -> int:
    n, m = map(int, input().split())
    worn = 0
    
    while n > 0:
        worn += 1
        n -= 1
        if worn % m == 0:
            n += 1
    
    return worn

print(problem460A())