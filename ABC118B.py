def ABC118B() -> int:
    n, m = map(int, input().split())
    foods_liked = {i: 0 for i in range(1, m + 1)}

    for _ in range(n):
        row = list(map(int, input().split()))
        for food in row[1:]:
            foods_liked[food] += 1

    everyone = 0  # foods liked by everyone
    for likes in foods_liked.values():
        if likes == n:
            everyone += 1

    return everyone

print(ABC118B())