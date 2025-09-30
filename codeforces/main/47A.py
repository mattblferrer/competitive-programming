def problem47A() -> str:
    triangulars = [n * (n + 1) // 2 for n in range(1, 50)]
    n = int(input())
    if n in triangulars:
        return "YES"
    return "NO"

print(problem47A())