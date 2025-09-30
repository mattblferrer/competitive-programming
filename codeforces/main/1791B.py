def problem1791B() -> str:
    _ = input()  # length of instructions string
    instructions = input()
    x, y = 0, 0  # current position of Alperen

    for i in instructions:
        if i == "L":
            x -= 1
        elif i == "R":
            x += 1
        elif i == "D":
            y -= 1
        elif i == "U":
            y += 1

        if x == 1 and y == 1:
            return "YES"

    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1791B())