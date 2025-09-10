def problem758A() -> int:
    _ = input()
    welfare = list(map(int, input().split(" ")))
    max_welfare = max(welfare)
    s = 0  # minimum burles that the kingdom has to spend
    
    for w in welfare:  # to make everyone equal, add burles to equal maximum
        s += max_welfare - w

    return s

print(problem758A())