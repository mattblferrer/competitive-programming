# generate triangular number of certain index
def triangular(ind: int) -> int:
    return ind*(ind+1)//2


# determines if number num is pentagonal
def is_pentagonal(num: int) -> bool:
    pent_check = ((24 * num + 1) ** 0.5 + 1) / 6
    return pent_check.is_integer()


# determines if number num is hexagonal
def is_hexagonal(num: int) -> bool:
    hex_check = ((8 * num + 1) ** 0.5 + 1) / 4
    return hex_check.is_integer()


def main():
    # given variables
    index = 286 
    triangle_num = triangular(index)  # starting triangle number

    # loop until triangle, pentagonal, hexagonal number found
    while not (is_pentagonal(triangle_num) and is_hexagonal(triangle_num)):
        index += 1
        triangle_num += index  # calculate next triangle number

    # print final result
    print("The next triangle number that is also pentagonal and hexagonal is "\
        f"{triangle_num}")


if __name__ == "__main__":
    main()
