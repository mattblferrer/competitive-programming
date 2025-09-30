def problem61A() -> str:
    x = input()
    y = input()
    result = ""
    for x_i, y_i in zip(x, y):
        if x_i != y_i:
            result += "1"
        else:
            result += "0"

    return result

print(problem61A())