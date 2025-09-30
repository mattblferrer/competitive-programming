from math import ceil

def problem1043A() -> int:
    n = int(input())
    a = list(map(int, input().split(' ')))
    votes = sum(a)

    return max(max(a), ceil((votes * 2 + 1) / n))

print(problem1043A())