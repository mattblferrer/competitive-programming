def problem49A() -> str:
    question = input()
    for char in question:
        if char.isalpha():
            last_letter = char

    if last_letter.lower() in 'aeiouy':  # vowel
        return "YES"
    return "NO"  # consonant

print(problem49A())