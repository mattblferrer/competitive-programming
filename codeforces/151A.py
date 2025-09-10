def problem151A() -> int:
    n, k, l, c, d, p, nl, np = map(int, input().split(" "))
    volume = k * l  # volume of drink in mL
    slices = c * d  # total slices of lime available
    return min(volume // nl, slices, p // np) // n

print(problem151A())