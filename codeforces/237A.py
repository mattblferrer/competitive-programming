def problem237A() -> int:
    n = int(input())
    times = {}

    for _ in range(n):
        hh, mm = map(int, input().split(" "))
        if (hh, mm) not in times:
            times[(hh, mm)] = 1
        else:
            times[(hh, mm)] += 1

    return max(times.values())

print(problem237A())