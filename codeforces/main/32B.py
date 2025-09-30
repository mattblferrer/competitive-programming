def problem32B() -> str:
    borze = input()
    ptr = 0  # pointer of current position in Borze code
    decoded = ""

    while ptr < len(borze):
        if borze[ptr] == ".":  # 0
            decoded += "0"
            ptr += 1
        elif borze[ptr:ptr + 2] == "-.":  # 1
            decoded += "1"
            ptr += 2
        else:  # 2
            decoded += "2"
            ptr += 2

    return decoded

print(problem32B())