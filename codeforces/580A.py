def problem580A() -> int:
    n = int(input())
    arr = list(map(int, input().split(' ')))
    current_length = 1
    maximum_length = 1

    for i, j in zip(arr, arr[1:]):
        if i > j:  # decreasing
            current_length = 1
        else:  # non-decreasing
            current_length += 1
            maximum_length = max(maximum_length, current_length)

    return maximum_length

print(problem580A())