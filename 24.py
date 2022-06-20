'''
PLAN:
Generate the 1,000,000th lexicographic permutation without calculating all the permutations

1. Calculate the factorial
2. Figure out which "group" the number 1,000,000 falls in
3. Generate the permutation left to right
4. If digit is used
'''


def factorial(n):
    fac = 1  # factorial
    for i in range(1, n + 1):
        fac *= i
    return fac


permIndexIn = 1000000
permIndex = permIndexIn - 1  # will be used for calculation (-1 because of zero index)
digits = 10  # number of digits used (0-9)
possiblePerms = factorial(digits)  # number of possible permutations of all the digits
usedDigits = [False for digit in range(digits)]  # digits used so far
permDigits = []  # digits in the permutation

for i in range(digits, 0, -1):  # iterate through all digits
    currentDigit = permIndex // (possiblePerms // i)  # get "group"
    permIndex -= currentDigit * (possiblePerms // i)
    possiblePerms //= i  # reduce the number of digits by 1

    # assign digit to lexicographical permutation
    ctr = 0  # to count the number of unused digits
    for j in range(digits):
        if not usedDigits[j]:
            if currentDigit == ctr:
                loopOut = j  # permutation digit
                break
            else:
                ctr += 1

    # mark digit as used
    permDigits.append(loopOut)
    usedDigits[loopOut] = True

# final output
output = ""
for i in permDigits:
    output = output + str(i)
print("Lexicographical permutation", permIndexIn, "is", output)
