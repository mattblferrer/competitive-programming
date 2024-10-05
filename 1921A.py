def problem1921A() -> int:
    coordinates = []
    for _ in range(4):  # get 4 corners of the square
        x, y = map(int, input().split(" "))
        coordinates.append((x, y))

    bottom_left = min(coordinates)
    top_right = max(coordinates)
    return (top_right[0] - bottom_left[0]) * (top_right[1] - bottom_left[1])

test_cases = int(input())
for _ in range(test_cases):
    print(problem1921A())