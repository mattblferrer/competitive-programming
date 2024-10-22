def problem867A() -> str:
    n = int(input())
    string = input()
    a, b = 0, 0  # F -> S, S -> F

    for left, right in zip(string, string[1:]):
        if left == "F" and right == "S":
            a += 1
        elif left == "S" and right == "F":
            b += 1

    if a < b:
        return "YES"
    return "NO"

print(problem867A())