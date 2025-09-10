def is_bouncy(num: int) -> bool:
    """returns True if a number num is bouncy, or has neither increasing nor
    decreasing digits, and False otherwise"""
    # number can't be bouncy below 100
    if num < 100:
        return False

    # check if number is supposed to be increasing or decreasing
    digits = str(num)
    is_increasing = True if digits[0] < digits[-1] else False

    # calculate differences between adjacent digits
    diff_array = [ord(next) - ord(prev) for prev, next in 
        zip(digits, digits[1:])]
    
    # check if number is bouncy based on differences
    for diff in diff_array:
        if (diff > 0 and not is_increasing) or (diff < 0 and is_increasing):
            return True
    return False


def main():
    # declare variables
    bouncy_num = 0
    n = 99

    # main loop
    while bouncy_num / n != 0.99:
        n += 1
        if is_bouncy(n):
            bouncy_num += 1

    # print result
    print(f"The least number for which the proportion is 99% is {n}")


if __name__ == "__main__":
    main()
