def ABC117B() -> str:
    n = int(input())
    sides = list(map(int, input().split()))
    total = sum(sides)
    max_l = max(sides)
    
    if max_l < total - max_l:
        return "Yes"
    return "No"

print(ABC117B())