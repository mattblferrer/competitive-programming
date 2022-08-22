import math


# function that converts decimal to binary
def dec_to_bin(num):
    highest_power2 = int(math.log2(num))  # get length of binary conversion

    bin_digits = [0]*(highest_power2+1)
    for i in range(highest_power2, -1, -1):  # loop through the powers of 2 starting from the highest
        if num >= 2**i:
            bin_digits[highest_power2-i] = 1
            num -= 2**i

    # convert binary digits list to string and return int equivalent
    bin_str = int(''.join(str(item) for item in bin_digits))
    return bin_str


# declare variables
n = 10**25

# print result
print(dec_to_bin(n))
