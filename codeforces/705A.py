def problem705A() -> str:
    n = int(input())
    string = "I hate that I love that " * ((n - 1) // 2)
    if n % 2 == 1:
        string += "I hate it"
    else:
        string += "I hate that I love it"

    return string

print(problem705A())