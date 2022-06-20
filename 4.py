# initialize output variable
largestPalindrome = 0

for i in range(100, 1000):
    for j in range(100, 1000):
        check = i*j  # generated 3 digit x 3 digit product
        if str(check) == str(check)[::-1] and check > largestPalindrome:  # check if palindrome
            largestPalindrome = check

print(largestPalindrome)
