def problem1372A() -> list[int]:
    n = int(input())
    arr = []
    for i in range(1, n + 1):
        if i % 2 == 0:
            arr.append(i - 1)
        else:
            arr.append(i)

    return arr

test_cases = int(input())
for _ in range(test_cases):
    print(*problem1372A())