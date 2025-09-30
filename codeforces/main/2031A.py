from collections import Counter

def problem2031A() -> int:
    n = int(input())
    h = list(map(int, input().split(' ')))
    counts = Counter(h)
    max_count = max(counts.values())
    return n - max_count

test_cases = int(input())
for _ in range(test_cases):
    print(problem2031A())