def problem1374B() -> int:
    n = int(input())
    moves = 0

    while n % 3 == 0:
        if n % 2 != 0:
            moves += 1
            n *= 2
        while n % 6 == 0:
            moves += 1
            n //= 6
        
    if n != 1:
        return -1
    return moves

test_cases = int(input())
for _ in range(test_cases):
    print(problem1374B())