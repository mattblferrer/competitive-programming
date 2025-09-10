def problem400A() -> tuple[int, list[str]]:
    string = input()
    ways = 0
    ab_pairs = []

    for a in [1, 2, 3, 4, 6, 12]:  # factors of 12
        b = 12 // a
        for i in range(b):
            if all(string[j] == "X" for j in range(i, 12, b)):
                ways += 1
                ab_pairs.append(f"{a}x{b}")
                break

    return ways, ab_pairs

test_cases = int(input())
for _ in range(test_cases):
    result = problem400A()
    print(result[0], *result[1])