def problem1926A() -> str:
    string = input()
    a, b = 0, 0
    for char in string:
        if char == "A":
            a += 1
        else:
            b += 1

    if a > b:
        return "A"
    return "B"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1926A())