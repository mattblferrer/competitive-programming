def problem501A() -> str:
    a, b, c, d = map(int, input().split(' '))
    misha = max(3 * a / 10, a - (a / 250 * c))
    vasya = max(3 * b / 10, b - (b / 250 * d))

    if misha > vasya:
        return "Misha"
    elif misha < vasya:
        return "Vasya"
    else:
        return "Tie"

print(problem501A())