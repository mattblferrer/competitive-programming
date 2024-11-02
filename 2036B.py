def problem2036B() -> int:
    n, k = map(int, input().split(' '))
    brands = {}

    for _ in range(k):
        b_i, c_i = map(int, input().split(' '))
        if b_i not in brands:
            brands[b_i] = c_i
        else:
            brands[b_i] += c_i

    profits = [(c_i, b_i) for b_i, c_i in brands.items()]
    return sum(c_i for c_i, b_i in sorted(profits, reverse=True)[:min(n, k)])

test_cases = int(input())
for _ in range(test_cases):
    print(problem2036B())