def ABC181B() -> int:
    n = int(input())
    total_sum = 0

    for _ in range(n):
        a_i, b_i = map(int, input().split())
        total_sum += (b_i * (b_i + 1)) // 2 - (a_i * (a_i - 1)) // 2

    return total_sum

print(ABC181B())