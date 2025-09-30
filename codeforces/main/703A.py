def problem703A() -> str:
    n = int(input())  # number of rounds
    m, c = 0, 0  # number of points for Mishka, Chris

    for _ in range(n):
        m_i, c_i = map(int, input().split(" "))
        if m_i > c_i:  # Mishka wins round
            m += 1
        elif m_i < c_i:  # Chris wins round
            c += 1
    
    if m > c:
        return "Mishka"
    elif m < c:
        return "Chris"
    else:  # draw
        return "Friendship is magic!^^"

print(problem703A())