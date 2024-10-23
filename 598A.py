def problem598A() -> int:
    n = int(input())
    all_sum = n * (n + 1) // 2
    power_2_sum = 2 ** (n.bit_length()) - 1
    return all_sum - 2 * power_2_sum

test_cases = int(input())
for _ in range(test_cases):
    print(problem598A())