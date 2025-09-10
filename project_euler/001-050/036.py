# function that converts decimal to binary
def dec_to_bin(num: int) -> str:
    bin_str = bin(num).replace("0b","")
    return bin_str


# function that tells if a number num is a palindrome
def is_palindrome(num: int) -> bool:
    return str(num) == str(num)[::-1]  # if num == reverse(num)


# function that tells if the number num is a palindrome in base 10 and 2
def is_double_palindrome(num: int) -> bool:
    return is_palindrome(num) and is_palindrome(dec_to_bin(num))


def main():
    limit = 1000000  # given variable

    # loop through all odd numbers from 1 to limit
    palindrome_sum = sum(i for i in range(1, limit, 2) if 
    is_double_palindrome(i))
    
    # print final result
    print("The sum of all numbers which are palindromic in base 10 "\
        f"and 2 is {palindrome_sum}")


if __name__ == "__main__":
    main()
