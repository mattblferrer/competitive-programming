def problem230A() -> str:
    s, n = map(int, input().split())
    dragons = []
    
    for _ in range(n):
        x_i, y_i = map(int, input().split())
        dragons.append((x_i, y_i))
    dragons.sort()

    for x_i, y_i in dragons:
        if s <= x_i:
            return "NO"   
        s += y_i
    return "YES"

print(problem230A())