def problem1986A() -> int:
    points = list(map(int, input().split(" ")))
    min_distance = float('inf')

    for i in range(1, 11):  # check distances of all points in [1, 10]
        distance = sum(abs(p - i) for p in points)
        min_distance = min(min_distance, distance)

    return min_distance


test_cases = int(input())
for _ in range(test_cases):
    print(problem1986A())