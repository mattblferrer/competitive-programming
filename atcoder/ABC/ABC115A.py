def ABC115A() -> str:
    d = int(input())
    if d == 25:
        return "Christmas"
    elif d == 24:
        return "Christmas Eve"
    elif d == 23:
        return "Christmas Eve Eve"
    elif d == 22:
        return "Christmas Eve Eve Eve"

print(ABC115A())