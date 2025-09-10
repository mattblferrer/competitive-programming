from collections import Counter

def problem2037A() -> int:
    n = int(input())
    a = list(map(int, input().split()))
    counts = Counter(a)
    score = sum(c // 2 for c in counts.values())
    return score

test_cases = int(input())
for _ in range(test_cases):
    print(problem2037A())