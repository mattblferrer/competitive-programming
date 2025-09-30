def problem617A() -> int:
    x = int(input())  # coordinate of friend's house
    if x % 5 == 0:
        return x // 5
    return x // 5 + 1

print(problem617A())