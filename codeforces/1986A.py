def problem1986A() -> int:
    points = list(map(int, input().split(" ")))
    return max(points) - min(points)

test_cases = int(input())
for _ in range(test_cases):
    print(problem1986A())