def problem769A() -> int:
    _ = input()
    years = sorted(list(map(int, input().split(" "))))
    x = (years[-1] - years[0]) // 2
    return years[0] + x

print(problem769A())