def problem1472B() -> str:
    _ = input()  # number of candies
    weights = input().split(" ")
    one, two = weights.count("1"), weights.count("2")

    if two % 2 == 1:  # need even number of 1s to balance out remaining 2 (>0)
        if one and one % 2 == 0:
            return "YES"
        return "NO"
    else:
        if one % 2 == 0:
            return "YES"
        return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1472B())