def problem1913A() -> tuple[int, int]:
    n = input()  # take as string to do string slicing
    for slice in range(1, len(n)):
        a = n[:slice]
        b = n[slice:]
        if a[0] == "0" or b[0] == "0":  # check for leading zero
            continue

        a = int(a)
        b = int(b)
        if a == 0 or b == 0:  # check if any equal to 0
            continue
        if a >= b:  # check if b > a
            continue
        return a, b

    return -1

test_cases = int(input())
for _ in range(test_cases):
    result = problem1913A()
    if result == -1:
        print("-1")
    else:
        print(result[0], result[1])