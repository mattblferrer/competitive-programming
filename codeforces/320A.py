def problem320A() -> str:
    n = input()
    while n:
        if n[-1:] == "1":
            n = n[:-1]
        elif n[-2:] == "14":
            n = n[:-2]
        elif n[-3:] == "144":
            n = n[:-3]
        else:
            return "NO"
    return "YES"

print(problem320A())