def problem1915C() -> str:
    _ = input()  # number of buckets
    total_squares = sum(list(map(int, input().split(" "))))

    if total_squares ** 0.5 == int(total_squares ** 0.5):  # check if square
        return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1915C())