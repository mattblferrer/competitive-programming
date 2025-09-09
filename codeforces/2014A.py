def problem2014A() -> int:
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    gold = 0
    given = 0

    for a_i in a:
        if a_i >= k:
            gold += a_i
        elif a_i == 0 and gold:
            given += 1
            gold -= 1

    return given

test_cases = int(input())
for _ in range(test_cases):
    print(problem2014A())