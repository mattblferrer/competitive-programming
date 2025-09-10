def problem1849A() -> int:
    b, c, h = map(int, input().split(' '))
    if (c + h) < b:
        return (c + h) * 2 + 1
    else:
        return b * 2 - 1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1849A())