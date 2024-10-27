def problem52A() -> int:
    n = int(input())
    a = list(map(int, input().split(' ')))
    counts = {1: 0, 2: 0, 3: 0}

    for a_i in a:
        counts[a_i] += 1

    return n - max(counts.values())
    
print(problem52A())