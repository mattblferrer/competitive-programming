def problem1873B() -> int:
    _ = input()  # number of digits to take product of
    digits = sorted(list(map(int, input().split(" "))))
    digits[0] += 1  # add to minimum for greatest product

    product = 1
    for d in digits:
        product *= d
    
    return product

test_cases = int(input())
for _ in range(test_cases):
    print(problem1873B())