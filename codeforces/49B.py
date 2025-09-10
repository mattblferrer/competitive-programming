def problem49B() -> int:
    def convertFromBase(n: int, base: int) -> int:
        converted = 0
        power = 1

        while n > 0:
            converted += (n % 10) * power
            n //= 10
            power *= base

        return converted

    a, b = map(int, input().split(' '))
    max_digit = int(max(max(d for d in str(a)), max(d for d in str(b))))
    digits = 0

    # convert a, b to base max_digit + 1
    a = convertFromBase(a, max_digit + 1)
    b = convertFromBase(b, max_digit + 1)
    sum_ab = a + b

    # get number of digits in a + b, base max_digit + 1
    while sum_ab > 0:
        sum_ab //= max_digit + 1
        digits += 1

    return digits
    
print(problem49B())