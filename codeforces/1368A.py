def problem1368A() -> int:
    a, b, n = map(int, input().split(" "))
    steps = 0
    while True:
        if a > b:
            b += a
        else:
            a += b
        steps += 1
        if a > n or b > n:
            return steps

test_cases = int(input())
for _ in range(test_cases):
    print(problem1368A())