def ABC076B() -> int:
    n = int(input())
    k = int(input())
    curr = 1

    for _ in range(n):
        if curr > k:  # operation B
            curr += k
        else:  # operation A
            curr *= 2

    return curr

print(ABC076B())