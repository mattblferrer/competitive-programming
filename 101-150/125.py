"""
We only have to check numbers n up to n^2 + (n-1)^2 = limit (10^8)
2n^2 - 2n + 1 = 10^8
(n)(n-1) = 5*10^7
n is approximately sqrt(10^8) / sqrt(2)
"""
from math import sqrt


# function that tells if a number num is a palindrome
def is_palindrome(num: int) -> bool:
    return str(num) == str(num)[::-1]  # if num == reverse(num)


def main():
    # declare variables
    limit = 10**8
    square_limit = int(sqrt(limit) // sqrt(2))
    palindromic_list = set()  # to account for repeated entries
    n = 1  # starting num

    # compute squares that will be used
    square_list = [i*i for i in range(square_limit)]

    # main loop
    while n < square_limit:
        p_sum = square_list[n]  # partial sum of squares
        
        for i in range(n+1, square_limit):
            p_sum += square_list[i]

            if p_sum >= limit:
                break

            if is_palindrome(p_sum):
                palindromic_list.add(p_sum)

        n += 1

    # print result
    cs_sum = sum(palindromic_list)  # consecutive square sum (final output)
    print("Sum of palindromic square sums:", cs_sum)


if __name__ == "__main__":
    main()
