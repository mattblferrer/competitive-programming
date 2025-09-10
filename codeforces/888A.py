def problem888A() -> int:
    _ = input()  # length of array
    arr = list(map(int, input().split(" ")))
    extrema = 0
    
    for a, b, c in zip(arr, arr[1:], arr[2:]):
        if a > b < c:  # local minimum
            extrema += 1
        elif a < b > c:  # local maximum
            extrema += 1

    return extrema

print(problem888A())