def problem1872A() -> int:
    a, b, c = map(int, input().split(" "))
    diff = max(a, b) - min(a, b)
    if diff % (2 * c):
        return diff // (2 * c) + 1
    return diff // (2 * c)

test_cases = int(input())
for _ in range(test_cases):
    print(problem1872A())