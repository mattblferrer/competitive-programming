def problem723A() -> int:
    coords = list(map(int, input().split(" ")))
    return max(coords) - min(coords)

print(problem723A())