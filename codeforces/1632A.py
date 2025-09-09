def problem1632A() -> str:
    n = int(input())
    s = input()
    if n > 2:
        return "NO"
    if s in ["00", "11"]:
        return "NO"
    return "YES"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1632A())