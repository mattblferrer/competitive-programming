# initialize output variable
largestPalindrome = 0

# brute-force palindrome search
for i in range(1000, 100, -1):
    for j in range(990, 100, -11):  # must be divisible by 11
        check = i*j  # generated 3 digit x 3 digit product
        if str(check) == str(check)[::-1] and check > largestPalindrome:  # check if palindrome
            largestPalindrome = check         

# print result
print(largestPalindrome)
