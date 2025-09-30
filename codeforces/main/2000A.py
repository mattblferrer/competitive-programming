def problem2000A() -> str:
    a = input()  # take input as string
    if len(a) < 3:
        return "NO"
    if a[:2] == "10" and int(a[2:]) >= 2:
        if len(a) - 2 == len(str(int(a[2:]))):  # check for leading zero exponent
            return "YES"
        return "NO"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem2000A())