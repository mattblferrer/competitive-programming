def problem1208A() -> int:
    a, b, n = map(int, input().split(" "))
    seq = [a, b, a ^ b]
    return seq[n % 3]

test_cases = int(input())
for _ in range(test_cases):
    print(problem1208A())