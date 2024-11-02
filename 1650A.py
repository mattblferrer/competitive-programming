def problem1650A() -> str:
    s = input()
    c = input()
    indices = [i for i, char in enumerate(s) if char == c]
    return "YES" if any(i % 2 == 0 for i in indices) else "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1650A())