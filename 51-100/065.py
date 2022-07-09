# returns the term needed for the continued fraction of e
def e_term(term):
    if term % 3 == 2:
        return ((term - 2)//3+1)*2
    else:
        return 1


# returns the nth convergent of e
def e_convergent(term):
    term -= 1  # offset
    numerator = 1
    denominator = e_term(term)

    # if 1st term
    if term == 0:
        return 2, 1

    # iterate upwards in the continued fraction
    for i in range(term-1, 0, -1):
        frac_term = e_term(i)

        # add current fraction to next term in continued fraction
        numerator += frac_term*denominator

        numerator, denominator = denominator, numerator  # reciprocal

    # add 2 to final fraction
    numerator += 2*denominator
    return numerator, denominator


# declare variables
sumOfDigits = sum(int(digit) for digit in str(e_convergent(100)[0]))

# print output
print("The sum of the digits of the 100th convergent of e is", sumOfDigits)
