def problem144A() -> int:
    n = int(input())  # number of soldiers
    soldiers = list(map(int, input().split(" ")))
    minimum, maximum = float('inf'), 0

    for i, s in enumerate(soldiers):  # find index of minimum and maximum found
        if s <= minimum:  # finds rightmost min index
            minimum = s
            min_i = i
        if s > maximum:  # finds leftmost max index
            maximum = s
            max_i = i

    if min_i < max_i:
        return (n - min_i - 1) + max_i - 1
    return (n - min_i - 1) + max_i

print(problem144A())