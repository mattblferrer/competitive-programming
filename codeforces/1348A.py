def problem1348A() -> int:
    n = int(input())  # maximum 2^n
    a, b = 0, 0
    a_piles, b_piles = 0, 0
    
    for i in range(n, 0, -1):  # add 2^i for all i until 2^n
        if a_piles == n // 2:  # if pile A is full
            b += 2 ** i
            b_piles += 1
        elif b_piles == n // 2:  # if pile B is full
            a += 2 ** i
            a_piles += 1
        elif a > b:  # add to smaller pile
            b += 2 ** i
            b_piles += 1
        else:
            a += 2 ** i
            a_piles += 1

    return abs(a - b)

test_cases = int(input())
for _ in range(test_cases):
    print(problem1348A())