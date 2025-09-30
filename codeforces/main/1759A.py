def problem1759A() -> str:
    s = input()
    test = "Yes" * 20
    if s in test:
        return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1759A())