def problem2033A() -> str:
    n = int(input())
    if n % 2 == 0:
        return "Sakurako"
    return "Kosuke"

test_cases = int(input())
for _ in range(test_cases):
    print(problem2033A())