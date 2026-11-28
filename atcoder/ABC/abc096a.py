def ABC096A() -> int:
    a, b = map(int, input().split(' '))
    if a > b:
        return a - 1
    return a

print(ABC096A())