def CSES1083() -> int:
    n = int(input())
    actual_sum = sum(map(int, input().split(" ")))
    expected_sum = n * (n + 1) // 2
    return expected_sum - actual_sum

print(CSES1083())