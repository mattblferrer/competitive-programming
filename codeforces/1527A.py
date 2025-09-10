def problem1527A() -> int:
    n = int(input())
    bit_length = 0
    while n > 0:
        n >>= 1
        bit_length += 1

    return 2 ** (bit_length - 1) - 1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1527A())