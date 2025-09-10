def problem1228A() -> int:
    l, r = map(int, input().split(" "))
    for x in range(l, r + 1):
        if len(set(str(x))) == len(str(x)):  # distinct digits check
            return x
        
    return -1

print(problem1228A())