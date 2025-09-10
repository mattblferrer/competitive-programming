from collections import Counter

def problem2037B() -> tuple[int, int]:
    k = int(input())
    a = Counter(input().split())
    k -= 2
    
    for i in a:
        i = int(i)
        if k % i != 0:
            continue
        if i == k // i:
            if a[str(i)] >= 2:
                return i, i
        elif a[str(k // i)] >= 1:
            return i, k // i

test_cases = int(input())
for _ in range(test_cases):
    print(*problem2037B())