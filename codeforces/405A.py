def problem405A() -> list[int]:
    _ = int(input())
    return sorted(list(map(int, input().split(' '))))

print(*problem405A())