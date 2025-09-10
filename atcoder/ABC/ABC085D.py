from math import ceil

def ABC085D() -> int:
    n, h = map(int, input().split())
    a, b = [], []

    for _ in range(n):
        a_i, b_i = map(int, input().split())
        a.append(a_i)
        b.append(b_i)

    max_a = max(a)  # max dmg katana when wielded
    throws = 0
    throw_n = 0
    b.sort(reverse=True)  # highest dmg katanas when thrown first

    for b_i in b:  # katanas which deal more damage than max wield when thrown
        if b_i > max_a:
            throws += b_i
            throw_n += 1
        if throws >= h:  # check if throwing katanas is enough 
            return throw_n
    
    return throw_n + ceil((h - throws) / max_a)
    
print(ABC085D())