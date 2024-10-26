def problem12A() -> str:
    pattern = []
    for _ in range(3):
        row = input()
        pattern.append(row)

    for i in range(3):
        for j in range(i, 3):
            if pattern[i][j] != pattern[2 - i][2 - j]:
                return "NO"
            
    return "YES"

print(problem12A())