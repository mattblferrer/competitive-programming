def problem742B() -> int:
    _, x = map(int, input().split(' '))
    array = list(map(int, input().split(' ')))
    counts = {}  # n: frequency pairs
    pairs = 0

    for k in array:  # get count of each element k in array
        if k not in counts:
            counts[k] = 1
        else:
            counts[k] += 1

    for k in array:  # search for xor in array
        xor = k ^ x
        pairs += counts.get(xor, 0)
        if xor == k:
            pairs -= 1
        
    return pairs // 2  # since both (a, b), (b, a) pairs counted

print(problem742B())