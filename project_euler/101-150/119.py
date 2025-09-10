from math import log


# returns the sum of the digits of num
def digit_sum(num: int) -> int:
    return sum([int(digit) for digit in str(num)])


# checks if num is a perfect power of a base
def is_power(num: int, base: int) -> bool:
    if base == 1:
        return False

    exp = round(log(num, base))  # round log to nearest whole number
    return base ** exp == num  # check if log is an integer


def main():
    # generate i^p up to reasonable limit
    limit = 100
    powers = sorted(list(
        {i ** p for p in range(1, limit) for i in range(1, limit)}))

    # iterate through powers
    a = 1
    for num in powers:
        if num > 10 and is_power(num, digit_sum(num)):
            print(a, num)
            a += 1

        if a > 30:
            break


if __name__ == "__main__":
    main()
