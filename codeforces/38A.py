def problem38A() -> int:
    _ = input()  # length of array d_i
    d_i = list(map(int, input().split(" ")))
    a, b = map(int, input().split(" "))
    return sum(d_i[a - 1: b - 1])

print(problem38A())