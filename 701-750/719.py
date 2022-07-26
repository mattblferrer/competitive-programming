"""
All S-numbers are congruent to 0 or 1 mod 9.
"""
from math import sqrt


# checks if a square number is an S number
def is_s_number(sqr, index):
    # declare variables
    string = str(sqr)
    subset_index = 1
    length = len(string) - 1

    while subset_index < 2 ** (length):
        subset_b = format(subset_index, "0" + str(length) + "b")

        # get subset of index subset_b and add terms
        split_index = [0]
        for i, digit in enumerate(subset_b):
            if digit == '1':
                split_index.append(i + 1)

        # split number according to split subset
        split_index.append(length + 1)
        split = [int(string[i:j]) for i, j in zip(split_index, split_index[1:])]
        nSum = sum(split)

        # splitting number check
        if nSum == index:
            print(index, string, split)
            return True

        subset_index += 1
    
    return False


# declare variables
limit = 10**12
sqr_limit = int(sqrt(limit))
sqr = 81
index = 9
sSum = 0  # sum of all S numbers (T(N))

# main loop
while index <= sqr_limit:
    if is_s_number(sqr, index):  # check 0 mod 9
        sSum += sqr

    sqr += 2 * index + 1
    index += 1

    if is_s_number(sqr, index):  # check 1 mod 9
        sSum += sqr

    # generate (i+8)^2
    sqr += 16*index + 64
    index += 8

# print result
print("T(10^12) =", sSum)
