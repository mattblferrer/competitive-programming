def problem1369A() -> str:
    n = int(input())  # number of sides
    if n % 4 == 0:
        return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1369A())