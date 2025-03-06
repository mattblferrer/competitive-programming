def ABC193C() -> int:
    n = int(input())
    powers = set()

    for i in range(2, int(n ** 0.5) + 1):
        j = 2
        power = i ** j
        while power <= n:
            powers.add(power)
            power *= i

    return n - len(powers)

print(ABC193C())