def ABC170D() -> int:
    n = int(input())
    a = list(map(int, input().split()))
    limit = max(a)
    sieve = [True] * (limit + 1)
    seen = set()
    duplicates = set()  # to filter out a_i == a_j

    # find duplicate a_i in arr a, otherwise sieve all multiples of a_i
    for a_i in a:
        for mult in range(2, limit // a_i + 1):
            sieve[a_i * mult] = False
        if a_i in seen:
            duplicates.add(a_i)
        seen.add(a_i)

    # count unique a_i not a multiple of any a_j
    count = 0
    for a_i in a:
        if sieve[a_i] and a_i not in duplicates:
            count += 1
            
    return count

print(ABC170D())