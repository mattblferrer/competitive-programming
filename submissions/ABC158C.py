from math import floor

def ABC158C() -> int:
    a, b = map(int, input().split())
    low = int(a / 0.08)
    high = int((b + 1) / 0.1 + 1)
    for price in range(low, high):
        if floor(price * 0.08) == a and floor(price * 0.1) == b:
            return price
    return -1

print(ABC158C())