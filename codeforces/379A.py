def problem379A() -> int:
    a, b = map(int, input().split(' '))
    hours = 0

    while a > 0:
        hours += 1  # use one candle
        a -= 1
        if hours % b == 0:  # extra candle
            a += 1
        
    return hours

print(problem379A())