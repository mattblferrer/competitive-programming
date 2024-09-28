def problem723A() -> int:
    coords = sorted(list(map(int, input().split(" "))))
    return (coords[2] - coords[1]) + (coords[1] - coords[0])

print(problem723A())