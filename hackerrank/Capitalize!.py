

# Complete the solve function below.
def solve(s):
    s = list(s)
    if s[0].islower():
        s[0] = chr(ord(s[0]) - 32)
    for i, c in enumerate(s):
        if c == " " and s[i + 1].islower():
            s[i + 1] = chr(ord(s[i + 1]) - 32)
            
    new_string = ""
    for c in s:
        new_string += c
        
    return new_string

