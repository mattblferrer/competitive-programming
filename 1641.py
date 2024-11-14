def CSES1641() -> str:
    n, x = map(int, input().split())
    a = list(map(int, input().split()))
    indices = {a_i: i for i, a_i in enumerate(a, start=1)}
    seen_a_i = set()

    for i, a_i in enumerate(a, start=1):
        if a_i in seen_a_i:
            continue
        seen_a_i.add(a_i)
        for j, a_j in enumerate(a[i:], start=i + 1):
            if x - a_i - a_j not in indices:
                continue
            if indices[x - a_i - a_j] in [i, j]:
                continue
            return f"{i} {j} {indices[x - a_i - a_j]}"
            
    return "IMPOSSIBLE"

print(CSES1641())