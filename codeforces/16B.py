def problem16B() -> int:
    n, m = map(int, input().split(" "))
    containers = []

    for _ in range(m):  # get container inputs
        a, b = map(int, input().split(" "))
        containers.append((b, a))
    containers.sort(reverse=True)  # sort by highest matches per matchbox
    
    matches = 0
    for b, a in containers:  # get maximal matchboxes first
        matches += min(n, a) * b  # make sure that n does not go negative
        n -= min(n, a)
        if n == 0:
            return matches
        
    return matches

print(problem16B())