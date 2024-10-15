def problem1650A() -> str:
    s = input()
    c = input()
    indices = []

    for i, char in enumerate(s):
        if char == c:
            indices.append(i)

    for i in indices:
        if i % 2 == 0:
            return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1650A())