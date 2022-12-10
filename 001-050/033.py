from math import gcd


# reduces fraction to its lowest terms
def reduce(numerator: int, denominator: int) -> tuple[int, int]:
    # divide numerator, denominator by their GCD
    frac_gcd = gcd(numerator, denominator)
    numerator //= frac_gcd
    denominator //= frac_gcd

    return numerator, denominator


# loop through all numerators up to a given denominator and cancel digits
def cancel_digits(denominator: int) -> tuple[int, int]:
    for numerator in range(10, denominator):
        # get digits of numerator and denominator in list
        numerator_digits = [digit for digit in str(numerator)]  
        denominator_digits = [digit for digit in str(denominator)]

        cancelable_digits = [digit for digit in numerator_digits 
            if digit in denominator_digits and digit != '0']  # intersection

        # iterate through all similar digits in numerator and denominator
        for digit in cancelable_digits:
            # if numerator and denominator don't have exactly the same digits
            if sorted(numerator_digits) == sorted(denominator_digits):
                continue

            # cancel digits
            if digit in numerator_digits and digit in denominator_digits:
                numerator_digits.remove(digit)
                denominator_digits.remove(digit)

            # merge digits back to int
            reduced_num = int("".join(numerator_digits))
            reduced_denom = int("".join(denominator_digits))

            # if denominator or numerator is 0, do not reduce
            if not reduced_num or not reduced_denom or (reduce(
                reduced_num, reduced_denom) != reduce(numerator, denominator)):
                continue

            return numerator, denominator


def main():
    # declare variables
    numerator_product, denominator_product = 1, 1

    # loop until all 4 2-digit solutions are found
    for d in range(10, 99):
        current_fractions = cancel_digits(d)
        if current_fractions:  # if solution is found
            print(current_fractions)
            numerator_product *= current_fractions[0]
            denominator_product *= current_fractions[1]

    # print final result
    numerator_product, denominator_product = reduce(
        numerator_product, denominator_product)
    print("The product of the four fractions is "\
        f"{numerator_product}/{denominator_product}")

    
if __name__ == "__main__":
    main()
