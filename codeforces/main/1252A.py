def problem1252A() -> list[int]:
    n = int(input())
    a = list(map(int, input().split()))
    b = []

    for k in a:
        b.append(n - k + 1)

    return b

print(*problem1252A())