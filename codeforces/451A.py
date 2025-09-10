def problem451A() -> str:
    n, m = map(int, input().split())
    if min(n, m) % 2 == 0:
        return "Malvika"
    return "Akshat"

print(problem451A())