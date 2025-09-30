def problem194A() -> int:
    n, k = map(int, input().split(' '))
    for fails in range(n):
        if 5 >= (k - 2 * fails) / (n - fails) >= 3:
            return fails
    return n

print(problem194A())