def CSES1068() -> list[int]:
    n = int(input())
    steps = [n]
    while steps[-1] != 1:
        if steps[-1] % 2 == 0:  # even, n // 2
            steps.append(steps[-1] // 2)
        else:  # odd, 3n + 1
            steps.append(steps[-1] * 3 + 1)

    return steps

print(*CSES1068())