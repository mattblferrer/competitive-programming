def problem1353B() -> int:
    _, k = map(int, input().split(" "))
    a = sorted(list(map(int, input().split(" "))))
    b = sorted(list(map(int, input().split(" "))), reverse=True)
    max_sum = sum(a_i for a_i in a[k:])  # guaranteed to not be swapped

    for a_i, b_i in zip(a[:k], b[:k]):
        max_sum += max(a_i, b_i)

    return max_sum

test_cases = int(input())
for _ in range(test_cases):
    print(problem1353B())