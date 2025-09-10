def problem1669B() -> int:
    _ = input()  # length of array
    arr = list(map(int, input().split(" ")))
    counts = {}

    for a in arr:  # get frequency of each element a in arr
        if a not in counts:
            counts[a] = 1
        else:
            counts[a] += 1
        if counts[a] == 3:
            return a

    return -1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1669B())