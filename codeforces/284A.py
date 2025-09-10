def problem284A() -> int:
    p = int(input())
    roots = 0

    for x in range(1, p):
        power = 1
        for _ in range(p - 2):
            power = (x * power) % p
            if (power - 1) % p == 0:
                break
        else:
            power = (x * power) % p
            if (power - 1) % p == 0:
                roots += 1

    return roots

print(problem284A())