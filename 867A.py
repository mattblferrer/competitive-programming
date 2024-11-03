def problem867A() -> str:
    n = int(input())
    string = input()
    if string[0] == "S" and string[-1] == "F":
        return "YES"
    return "NO"

print(problem867A())