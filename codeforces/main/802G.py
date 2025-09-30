def problem802G() -> str:
    string = input()
    ptr = 0
    match_string = "heidi"

    for char in string:
        if char == match_string[ptr]:
            ptr += 1
        if ptr == len(match_string):
            return "YES"
    return "NO"

print(problem802G())