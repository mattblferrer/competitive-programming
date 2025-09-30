def problem702A() -> int:
    _ = input()  # length of array
    arr = list(map(int, input().split(" ")))
    length = 1
    max_length = 1

    for a, b in zip(arr, arr[1:]):
        if a < b:
            length += 1
            max_length = max(length, max_length)
        else:
            length = 1

    return max_length

print(problem702A())