def problem514A() -> str:
    x = input()
    new_x = ""

    for digit in x:
        if int(digit) >= 5:
            new_x += str(9 - int(digit))
        else:
            new_x += digit

    if new_x[0] == "0":
        return x[0] + new_x[1:]
    return new_x

print(problem514A())