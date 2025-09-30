from math import ceil

def problem1932B() -> int:
    n = int(input())
    a = list(map(int, input().split()))
    curr = 0  # current year

    for a_i in a:
        curr = ceil((curr + 1) / a_i) * a_i

    return curr

test_cases = int(input())
for _ in range(test_cases):
    print(problem1932B())