def problem75A() -> str:
    a = input()
    b = input()
    sum_no_zeros = int(str(int(a) + int(b)).replace("0", ""))
    sum_ab = int(a.replace("0", "")) + int(b.replace("0", ""))

    if sum_ab == sum_no_zeros:
        return "YES"
    return "NO"

print(problem75A())