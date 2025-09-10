def problem134A() -> tuple[int, list[int]]:
    n = int(input())
    a = list(map(int, input().split(' ')))
    sum_all = sum(a)
    mean_all = sum_all / n
    indices = []

    for i, a_i in enumerate(a, start=1):
        if a_i == mean_all:
            indices.append(i)

    return len(indices), indices

result = problem134A()
print(result[0])
print(*result[1])