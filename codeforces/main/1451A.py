def problem1451A() -> int:
    n = int(input())
    if n == 1:  # 1
        return 0
    if n == 2:  # 2 -> 1
        return 1
    if n == 3:  # 3 -> 2 -> 1
        return 2
    if n % 2 == 1:  # (2k + 1) -> 2k -> 2 -> 1
        return 3
    else:  # 2k -> 2 -> 1
        return 2

test_cases = int(input())
for _ in range(test_cases):
    print(problem1451A())
