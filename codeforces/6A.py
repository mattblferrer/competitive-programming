from itertools import combinations

def problem6A() -> str:
    sides = list(map(int, input().split()))
    best = "IMPOSSIBLE"
    for a, b, c in combinations(sides, 3):
        if a + b > c and a + c > b and b + c > a:
            return "TRIANGLE"
        if a + b == c or a + c == b or b + c == a:
            best = "SEGMENT"
    return best

print(problem6A())