def problem1351B() -> str:
    a1, b1 = map(int, input().split(' '))
    a2, b2 = map(int, input().split(' '))
    if max(a1, b1) == max(a2, b2) and min(a1, b1) + min(a2, b2) == max(a1, b1):
        return "Yes"
    return "No"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1351B())