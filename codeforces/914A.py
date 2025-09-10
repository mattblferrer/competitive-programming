def problem914A() -> int:
    n = int(input())
    a = list(map(int, input().split(' ')))
    max_non_square = -float('inf')

    for a_i in a:
        if a_i < 0 or (a_i ** 0.5) != round(a_i ** 0.5):
            max_non_square = max(max_non_square, a_i)

    return max_non_square

print(problem914A())