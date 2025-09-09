def problem897B() -> int:
    k, p = map(int, input().split(' '))
    total_sum = 0

    for i in range(1, k + 1):
        total_sum += int(str(i) + str(i)[::-1])

    return total_sum % p

print(problem897B())