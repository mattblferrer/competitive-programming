def problem2024A() -> int:
    a, b = map(int, input().split())
    if a >= b:
        return a
    elif 2 * a < b:
        return 0
    else:
        return a - (b - a) 

test_cases = int(input())
for _ in range(test_cases):
    print(problem2024A())