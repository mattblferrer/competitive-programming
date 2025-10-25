s = input()

def solve(s):
    if s.count("1") > s.count("0"):
        return "0" * len(s)
    elif s.count("1") < s.count("0"):
        return "1" * len(s)
    if s[0] == "1":
        return "0" + "1" * (len(s) - 1)
    return "1" + "0" * (len(s) - 1)
    

print(solve(s))