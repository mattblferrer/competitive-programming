# function that converts decimal to binary
def dec_to_bin(num):
    bin_str = bin(num).replace("0b","")
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

    # loop through all odd numbers from 1 to limit
    palindrome_sum = sum(i for i in range(1, limit, 2) if is_double_palindrome(i))
    
    # print final result
    print(f"The sum of all numbers which are palindromic in base 10 and 2 is {palindrome_sum}")


main()
