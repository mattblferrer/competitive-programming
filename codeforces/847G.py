def problem847G() -> int:
    n = int(input())
    groups = [input() for _ in range(n)]
    classes = [0] * 7
    for group in groups:
        for i, c in enumerate(group):
            if c == "1":
                classes[i] += 1
    return max(classes)

print(problem847G())