def problem2024B() -> int:
    n, k = map(int, input().split())
    a = sorted(map(int, input().split()))

    previous = 0  # a_(i - 1), 0 if i = 0
    total_sum = 0
    total_sums = []
    for i, a_i in enumerate(a):  # how much lemonade can you get at each a_i
        total_sum += (n - i) * (a_i - previous)
        previous = a_i
        total_sums.append(total_sum)

    left, right = 0, n - 1    
    while left < right:  # binary search
        guess = (left + right) // 2
        if total_sums[guess] < k:
            left = guess + 1
        else:
            right = guess

    return k + left
    
t = int(input())
for _ in range(t):
    print(problem2024B())