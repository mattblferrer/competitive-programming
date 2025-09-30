def problem893B() -> int:  
    n = int(input())

    # generate beautiful numbers up to n
    beautiful = [1]
    k = 2
    while beautiful[-1] < n:
        beautiful.append((2 ** k - 1) * 2 ** (k - 1))
        k += 1  

    for b in reversed(beautiful):  # from biggest to smallest
        if n % b == 0:
            return b

print(problem893B())