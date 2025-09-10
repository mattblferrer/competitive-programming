def problem386A() -> tuple[int, int]:
    n = int(input())
    p = list(map(int, input().split()))

    maximum = 0
    max_index = 0
    for i, p_i in enumerate(p):
        if maximum < p_i:
            maximum = p_i
            max_index = i

    return max_index + 1, sorted(p)[-2]

print(*problem386A())