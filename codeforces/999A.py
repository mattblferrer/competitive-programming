def problem999A() -> int:
    n, k = map(int, input().split(' '))
    problems = list(map(int, input().split(' ')))

    for i in range(n):  # from left end of list
        if problems[i] > k:
            solved = i
            
            break
    else:  # can solve all problems (from left or right end)
        return n
    
    for i in range(n - solved):  # from right end of list
        if problems[n - i - 1] > k:
            solved += i
            break

    return solved

print(problem999A())