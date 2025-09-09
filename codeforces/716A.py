def problem716A() -> int:
    _, c = map(int, input().split(' '))
    t = list(map(int, input().split(' ')))
    words = 1
    
    for a, b in zip(t, t[1:]):
        if b - a > c:
            words = 1
        else:
            words += 1

    return words

print(problem716A())