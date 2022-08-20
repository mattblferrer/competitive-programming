for i in range(100000, 1000000):  # number has to have at least 6 digits
    # digits in i
    temp = i
    digits = set()
    while i > 0:
        digits.add(i % 10)
        i //= 10

    # used digits across i, 2i, 3i, 4i, 5i, 6i
    totalUsedDigits = set()
    for j in range(1, 7):
        mult = temp*j  # multiples of i
        while mult > 0:
            totalUsedDigits.add(mult % 10)
            mult //= 10

        if len(totalUsedDigits) > 6:  # no point to check further
            break

    # check if digits used are the same
    if len(digits) == 6 and len(totalUsedDigits) == 6:
        print(temp)  # print answer
        break
