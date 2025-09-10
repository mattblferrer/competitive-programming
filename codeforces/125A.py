def problem125A() -> tuple[int, int]:
    n = int(input())
    return (n + 1) // 36, ((n + 1) % 36) // 3

print(*problem125A())