def problem2027A() -> int:
    n = int(input())
    max_w, max_h = 0, 0
    for _ in range(n):
        w, h = map(int, input().split())
        max_w = max(max_w, w)
        max_h = max(max_h, h)

    return 2 * max_w + 2 * max_h

test_cases = int(input())
for _ in range(test_cases):
    print(problem2027A())