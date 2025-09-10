def ABC104B() -> str:
    s = input()
    if s[0] != "A":
        return "WA"
    if s[2:-1].count("C") != 1:
        return "WA"
    upper = 0
    for c in s:
        if c.isupper():
            upper += 1

    if upper != 2:
        return "WA"
    return "AC"

print(ABC104B())