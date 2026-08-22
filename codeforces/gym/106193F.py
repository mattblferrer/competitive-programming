def solve():
    ab, c = input().split()
    
    cl = len(c)
    if (len(ab) - cl + 1) % 2 == 0:
        bl = (len(ab) - cl + 1) // 2
        print(ab[:len(ab) - bl], ab[len(ab) - bl:])
    else:
        bl = (len(ab) - cl) // 2
        print(ab[:len(ab) - bl], ab[len(ab) - bl:])

solve()