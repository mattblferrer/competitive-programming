def problem443A() -> int:
    set_input = input()[1:-1]  # remove opening, closing brackets
    if set_input:
        letters = set_input.split(", ")
        return len(set(letters))
    return 0

print(problem443A())