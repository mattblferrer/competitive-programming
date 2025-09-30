def problem755A() -> int:
    n = int(input())
    if n == 1:
        return 3  # 1*3 + 1 = 4
    if n == 2:
        return 4  # 2*4 + 1 = 9
    return n - 2  # n * (n - 2) + 1 = n^2 - 2n + 1 = (n - 1)^2

print(problem755A())