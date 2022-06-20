import math


# function that converts decimal to binary
def dec_to_bin(num):
    highestPower2 = int(math.log2(num))  # get length of binary conversion

    binDigits = [0 for i in range(highestPower2+1)]
    for i in range(highestPower2, -1, -1):  # loop through the powers of 2 starting from the highest
        if num >= 2**i:
            binDigits[highestPower2-i] = 1
            num -= 2**i

    print(binDigits)

# function that tells if the number num is a palindrome in base 10 and 2
def is_double_palindrome(num):
    # TODO

dec_to_bin(585)
