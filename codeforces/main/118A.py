def problem118A() -> str:
    string = input().lower()
    new_string = ""
    
    for char in string:
        if char not in 'aoyeui':  # check if consonant (not vowel)
            new_string += "." + char

    return new_string

print(problem118A())