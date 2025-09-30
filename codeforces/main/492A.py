def problem492A() -> int:
    n = int(input())
    height = 0
    total_cubes = 0

    while total_cubes <= n:
        height += 1
        total_cubes += height * (height + 1) // 2
    
    return height - 1  # since final row incomplete

print(problem492A())