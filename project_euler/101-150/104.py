# checks if a number num is pandigital
def pandigital_check(num: int) -> bool:
    digits_used = {int(digit) for digit in str(num)}
    return digits_used == set(range(1, 10))


def main():
    # declare variables
    a, b = 1, 1  # starting Fibonacci numbers
    ctr = 2  # Fibonacci index

    # get first 16 digit Fibonacci numbers
    while True:
        if a > 10**15:
            # last 9 digits
            a_last, b_last = a % 10**9, b % 10**9

            # first 16 digits (for imprecision)
            a_first, b_first = a // 10, b // 10
            break
        
        a, b = b, a+b   
        ctr += 1

    # calculate F(k) mod 10^16 for first digits and 10^9 for last digits
    while not (pandigital_check(b_last) and pandigital_check(str(b_first)[:9])):
        a_last, b_last = b_last, (a_last + b_last) % 10**9
        a_first, b_first = b_first, a_first + b_first

        # check if first digits have > 16 digits (precision wiggle room)
        if b_first > 10**16:
            a_first //= 10
            b_first //= 10

        ctr += 1  # increment index

    # print results
    print(f"k: {ctr}")


if __name__ == "__main__":
    main()
        