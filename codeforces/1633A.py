def problem1633A() -> int:
    n = int(input())
    if n % 7 == 0:
        return n
    for digit in range(7):  # change last digit until divisible by 7
        if (n - n % 10 + digit) % 7 == 0:
            return n - n % 10 + digit

test_cases = int(input())
for _ in range(test_cases):
    print(problem1633A())