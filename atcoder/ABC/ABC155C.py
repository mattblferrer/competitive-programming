def ABC155C() -> None:
    n = int(input())
    counts = {}
    max_count = 0
    
    for _ in range(n): 
        s_i = input()
        if s_i not in counts:
            counts[s_i] = 1
        else:
            counts[s_i] += 1
        max_count = max(max_count, counts[s_i])

    result = sorted([string for string, count in counts.items() 
                     if count == max_count])
    for string in result:
        print(string)

ABC155C()