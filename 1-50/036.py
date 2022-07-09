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


# function that tells if a number num is a palindrome
def is_palindrome(num):
    if str(num) == str(num)[::-1]:  # if num == reverse(num)
        return True
    return False


# function that tells if the number num is a palindrome in base 10 and 2
def is_double_palindrome(num):
    if is_palindrome(num) and is_palindrome(dec_to_bin(num)):
        return True
    return False


def main():
    # given variables
    limit = 1000000
    palindrome_sum = 0  # output

    # loop through all numbers from 1 to limit
    for i in range(1, limit):
        if is_double_palindrome(i):
            palindrome_sum += i

    # print final result
    print("The sum of all numbers which are palindromic in base 10 and 2 is", palindrome_sum)


main()
