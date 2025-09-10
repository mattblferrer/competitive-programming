def problem731A() -> int:
    string = 'a' + input()
    rotations = 0
    
    for c, n in zip(string, string[1:]):  # current, next
        diff = ord(n) - ord(c)
        rotations += min(abs(diff), 26 - abs(diff))

    return rotations

print(problem731A())
