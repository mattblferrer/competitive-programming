def problem793A() -> int:
    n, k = map(int, input().split(' '))
    a = list(map(int, input().split(' ')))
    remainder = a[0] % k

    for a_i in a:
        if a_i % k != remainder:
            return -1
        
    minimum = min(a)
    seconds = 0
    for a_i in a:
        seconds += (a_i - minimum) // k

    return seconds

print(problem793A())