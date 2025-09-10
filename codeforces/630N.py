def problem630N() -> tuple[float, float]:
    a, b, c = map(int, input().split(' '))
    # use quadratic formula
    x1 = (-b + (b*b - 4*a*c) ** 0.5) / (2*a)
    x2 = (-b - (b*b - 4*a*c) ** 0.5) / (2*a)
    return max(x1, x2), min(x1, x2)

print(*problem630N(), sep="\n")