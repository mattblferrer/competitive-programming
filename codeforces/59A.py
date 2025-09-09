def problem59A() -> str:
    word = input()
    uppers, lowers = 0, 0  # number of uppercase, lowercase letters

    for letter in word:  # count uppercase, lowercase
        if letter.isupper():
            uppers += 1
        else:
            lowers += 1

    if uppers > lowers:
        return word.upper()
    return word.lower()

print(problem59A())