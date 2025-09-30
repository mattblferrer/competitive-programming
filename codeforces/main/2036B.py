def problem2036B() -> int:
    n, k = map(int, input().split(' '))
    brands = {}

    for _ in range(k):
        b_i, c_i = input().split(' ')
        if b_i not in brands:
            brands[b_i] = int(c_i)
        else:
            brands[b_i] += int(c_i)
            
    return sum(sorted(brands.values(), reverse=True)[:min(n, k)])

test_cases = int(input())
for _ in range(test_cases):
    print(problem2036B())