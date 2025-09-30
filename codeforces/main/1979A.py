def problem1979A() -> int:
    n = int(input())
    arr = list(map(int, input().split()))
    min_array_max = float('inf')

    for a, b in zip(arr, arr[1:]):
        min_array_max = min(min_array_max, max(a, b))

    return min_array_max - 1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1979A())