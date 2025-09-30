def problem411A() -> str:
    password = input()
    if len(password) < 5:
        return "Too weak"
    
    has_digit = False
    has_large = False
    has_small = False
    for char in password:
        if char.isdigit():
            has_digit = True
        elif char.isupper():
            has_large = True
        elif char.islower():
            has_small = True

    if has_digit and has_large and has_small:
        return "Correct"
    return "Too weak"

print(problem411A())