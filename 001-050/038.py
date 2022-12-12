"""
We only have to check integers from 2 to 9999, as when 10000 is multiplied 
by 2, the resulting concatenated product exceeds 9 digits in length
"""


# returns the concatenated product of a number num
def conc_product(num: int) -> str:
    concatenated_product = str(num)
    n = 2  # multiplier

    while len(concatenated_product) < 9:
        concatenated_product += str(num * n)
        n += 1

    return concatenated_product


# checks if a number num is pandigital
def pandigital_check(num: int) -> bool:
    digits_used = {int(digit) for digit in str(num)}
    return digits_used == set(range(1, 10)) and len(str(num)) == 9


def main():
    # declare variables
    maximum_product = 0

    # main loop
    for i in range(2, 10000):
        p = int(conc_product(i))
        is_pandigital = pandigital_check(p)
        
        if is_pandigital and maximum_product < p:  # check against maximum
            maximum_product = p

    # print result
    print("The largest 1 to 9 pandigital number that can be formed in this "\
        f"way is {maximum_product}")


if __name__ == "__main__":
    main()
