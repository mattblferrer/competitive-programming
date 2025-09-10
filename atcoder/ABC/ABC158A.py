def ABC158A() -> str:
    s = input()
    return "No" if s[0] == s[1] == s[2] else "Yes"

print(ABC158A())