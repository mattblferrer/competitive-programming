def swap_case(s):
    new_s = ""
    for char in s:
        if 64 < ord(char) <= 64 + 26:
            new_s += chr(ord(char) + 32)
        elif 96 < ord(char) <= 96 + 26:
            new_s += chr(ord(char) - 32)
        else:
            new_s += char
    return new_s

