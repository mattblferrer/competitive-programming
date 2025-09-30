def problem318A() -> int:
    n, k = map(int, input().split(" "))
    if k > (n + 1) // 2:  # even
        return (k - (n + 1) // 2) * 2
    else:  # odd
        return k * 2 - 1

print(problem318A())