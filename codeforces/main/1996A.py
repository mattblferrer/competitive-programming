def problem1996A() -> int:
    n = int(input())
    if n % 4 == 2:  # n // 4 cows + 1 chicken
        return n // 4 + 1
    return n // 4  # n // 4 cows

test_cases = int(input())
for _ in range(test_cases):
    print(problem1996A())