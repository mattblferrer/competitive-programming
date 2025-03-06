def ABC117D() -> int:
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    x = 0
    bit_counts = [0] * 64

    for a_i in a:
        binary = bin(a_i)[2:]
        for i, bit in enumerate(reversed(binary)):
            bit_counts[i] += int(bit)

    for i in range(63, -1, -1):
        if x + 2 ** i > k:
            continue
        if bit_counts[i] < n / 2:
            x += 2 ** i
            
    return sum(x ^ a_i for a_i in a)

print(ABC117D())