def problem44A() -> int:
    n = int(input())
    leaves = set(input() for _ in range(n))
    return len(leaves)

print(problem44A())