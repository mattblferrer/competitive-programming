def main(): 
    for i in range(100_000, 1_000_000):  # number has to have at least 6 digits
        digits = {int(digit) for digit in str(i)}  # digits in i
        total_used_digits = set()  # used digits across i, 2i, 3i, 4i, 5i, 6i

        for multiple in range(i, 7 * i, i):
            total_used_digits.update({int(digit) for digit in str(multiple)})
            if len(total_used_digits) > 6:  # no point to check further
                break

        # check if digits used are the same
        if len(digits) == len(total_used_digits) == 6:
            print(i)  # print answer
            break


if __name__ == "__main__":
    main()
