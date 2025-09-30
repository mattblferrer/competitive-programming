def problem431A() -> int:
    a = list(map(int, input().split(" ")))
    s = input()
    calories = sum(a[int(n) - 1] for n in s)
    return calories

print(problem431A())