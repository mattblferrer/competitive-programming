def problem2032A() -> tuple[int, int]:
    n = int(input())
    a = list(map(int, input().split(' ')))
    on = sum(a)
    if on <= n:
        return on % 2, on
    else:
        return on % 2, 2 * n - on

test_cases = int(input())
for _ in range(test_cases):
    print(*problem2032A())