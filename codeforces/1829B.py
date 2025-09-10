def problem1829B() -> int:
    _ = input()  # length of binary array
    arr = list(map(int, input().split(" ")))
    length = 0
    max_length = 0

    for a_i in arr:
        if a_i == 0:
            length += 1
            max_length = max(max_length, length)
        else:
            length = 0

    return max_length

test_cases = int(input())
for _ in range(test_cases):
    print(problem1829B())