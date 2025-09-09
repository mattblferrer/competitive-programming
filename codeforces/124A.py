def problem124A() -> int:
    n, a, b = map(int, input().split(' '))
    positions = 0
    for i in range(1, n + 1):
        if i > a and n - i <= b:
            positions += 1 

    return positions

print(problem124A())