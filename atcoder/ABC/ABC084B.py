def ABC084B() -> str:
    a, b = map(int, input().split())
    s = input()

    for i, char in enumerate(s):
        if i == a and char != "-":
            return "No"
        elif i != a and not char.isdigit():
            return "No"
    return "Yes"

print(ABC084B())