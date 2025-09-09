def problem131A() -> str:
    string = input()
    if len(string) == 1:
        return string.swapcase()

    if string[1:].isupper():  # check if follows caps lock rule
        if string[0].isupper():
            return string.lower()
        else:
            return string.capitalize()
        
    return string  # no need to change

print(problem131A())