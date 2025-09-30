def problem938A() -> str:
    n = int(input())
    s = input()
    word = s[0]  # corrected word

    for char in s[1:]:
        if word[-1] in "aeiouy" and char in "aeiouy":
            continue
        word += char

    return word

print(problem938A())