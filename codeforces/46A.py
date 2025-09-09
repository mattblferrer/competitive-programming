def problem46A() -> list[int]:
    n = int(input())
    curr = 0
    children = []
    for i in range(1, n):
        curr = (curr + i) % n
        children.append(curr + 1)
    return children

print(*problem46A())