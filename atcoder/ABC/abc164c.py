def ABC164C() -> int:
    n = int(input())
    seen = set()

    for _ in range(n):
        item = input()
        seen.add(item)

    return len(seen)

print(ABC164C())