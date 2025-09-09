def problem811A() -> str:
    a, b = map(int, input().split(' '))
    step = 0

    while a >= 0 and b >= 0:
        step += 1
        if step % 2 == 0:  # even candies, Valera's turn
            b -= step
        else:  # odd candies, Vladik's turn
            a -= step
        
    if step % 2 == 0:
        return "Valera"
    else:
        return "Vladik"

print(problem811A())