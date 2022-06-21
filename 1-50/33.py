import math


# reduces fraction to its lowest terms
def reduce(numerator, denominator):
    # divide numerator, denominator by their GCD
    gcd = math.gcd(numerator, denominator)
    numerator //= gcd
    denominator //= gcd

    return numerator, denominator


# loop through all numerators up to a given denominator and cancel digits
def cancel_digits(denominator):
    for numerator in range(10, denominator):
        numerator_digits = [digit for digit in str(numerator)]  # get digits of numerator
        denominator_digits = [digit for digit in str(denominator)]  # get digits of denominator

        cancelable_digits = [digit for digit in numerator_digits if digit in denominator_digits]  # intersection
        cancelable_digits = [digit for digit in cancelable_digits if digit != '0']  # remove 0s (trivial)

        # iterate through all similar digits in numerator and denominator
        for digit in cancelable_digits:
            # if numerator and denominator don't have exactly the same digits
            if sorted(numerator_digits) != sorted(denominator_digits):
                # cancel digits
                if digit in numerator_digits and digit in denominator_digits:
                    numerator_digits.remove(digit)
                    denominator_digits.remove(digit)

                # merge digits back to int
                reduced_num = int("".join(numerator_digits))
                reduced_denom = int("".join(denominator_digits))

                # if denominator or numerator is 0, do not reduce
                if reduced_num and reduced_denom:
                    if reduce(reduced_num, reduced_denom) == reduce(numerator, denominator):
                        return numerator, denominator


# declare variables
fractionNum = 0  # current number of digit cancelling fractions
numeratorProduct = 1
denominatorProduct = 1

# loop until all 4 2-digit solutions are found
for d in range(10, 99):
    currentFractions = cancel_digits(d)
    if currentFractions is not None:  # if solution is found
        print(currentFractions)
        numeratorProduct *= currentFractions[0]
        denominatorProduct *= currentFractions[1]

# print final result
finalFraction = reduce(numeratorProduct, denominatorProduct)
numeratorProduct = finalFraction[0]
denominatorProduct = finalFraction[1]
print("The product of the four fractions is {}/{}".format(numeratorProduct, denominatorProduct))
