def problem1619B() -> int:
    n = int(input())
    squares = int(round(n ** (1/2), 8))  # account for floating point errors
    cubes = int(round(n ** (1/3), 8))
    both = int(round(n ** (1/6), 8))
    return squares + cubes - both

test_cases = int(input())
for _ in range(test_cases):
    print(problem1619B())