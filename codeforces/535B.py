def problem535B() -> int:
    n = input()
    mask = [1]
    for digit in n:
        if digit == "4":
            mask.append(0)
        elif digit == "7":
            mask.append(1)

    index = 0
    for i, digit in enumerate(mask[::-1]):
        index += 2 ** i * digit

    return index - 1

print(problem535B())