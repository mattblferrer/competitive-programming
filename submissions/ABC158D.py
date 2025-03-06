from collections import deque

def ABC158D() -> str:
    s = deque(input())
    reverse = 0
    q = int(input())
    for _ in range(q):
        q_i = input()
        if q_i[0] == "1":  # reverse string
            reverse = 1 - reverse  # flip bit 
        else:  
            q_i, f_i, c_i = q_i.split()
            if int(f_i) - 1 == reverse:
                s.appendleft(c_i)
            else:
                s.append(c_i)

    if reverse:
        return "".join(reversed(s))
    return "".join(s)

print(ABC158D())