# returns the sum of the factorials of the digits of num
def fac_digit_sum(num):
    factorial_list = [1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880]  # pre-computed list of all factorials 0-9
    factorial_sum = 0

    digits = [int(digit) for digit in str(i)]

    # take factorials of digits
    for digit in digits:
        factorial_sum += factorial_list[digit]

    return factorial_sum


# TODO main function
