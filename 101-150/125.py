"""
We only have to check numbers n up to n^2 + (n-1)^2 = limit (10^8)
2n^2 - 2n + 1 = 10^8
(n)(n-1) = 5*10^7
n is approximately sqrt(10^8) / sqrt(2)
"""
from math import sqrt


# function that tells if a number num is a palindrome
def is_palindrome(num):
    if str(num) == str(num)[::-1]:  # if num == reverse(num)
        return True
    return False


# declare variables
limit = 10**8
squareLimit = int(sqrt(limit) // sqrt(2)) + 1
squareList = []  # precomputed list of squares
palindromicList = set()  # to account for repeated entries
csSum = 0  # consecutive square sum (final output)
n = 1  # starting num

# compute squares that will be used
for i in range(squareLimit):
    squareList.append(i**2)

# main loop
while n < squareLimit:
    pSum = squareList[n]  # partial sum of squares
    
    for i in range(n+1, squareLimit):
        pSum += squareList[i]

        if pSum >= limit:
            break

        if is_palindrome(pSum):
            if pSum not in palindromicList:
                palindromicList.add(pSum)
                csSum += pSum

    n += 1

# print result
print("Sum of palindromic square sums:", csSum)
