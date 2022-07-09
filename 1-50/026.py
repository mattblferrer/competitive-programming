"""
PLAN:
Implement long division manually in Python, use that function to get lengths of recurring cycles
"""


# get length of recurring cycle of decimal fraction
def recurring_cycle(n):
    # declare quotient, remainder lists
    quotients = []
    remainders = []

    # starting dividend
    dividend = 10

    # continued long division
    for i in range(n+n//10):  # only have to check up to n
        if dividend // n == 0:  # multiply dividend by 10 and move to the right
            dividend *= 10
            quotients.append(0)
            remainders.append(dividend % n)

        else:
            # long division step
            quotient = dividend // n
            remainder = dividend % n
            dividend = remainder*10

            # check for recurring cycle
            if remainder == 0:  # if expansion terminates
                return 0
            else:
                quotients.append(quotient)
                remainders.append(remainder)
                for j in range(len(quotients)-1):
                    if quotients[j] == quotient and remainders[j] == remainder:
                        return i-j


# given parameters
d = 1000
longestCycle = 0

# iterate from 2 to d
for i in range(2, d):
    currentCycle = recurring_cycle(i)
    if currentCycle > longestCycle:
        longestCycle = i

# final output
print("The number with the longest recurring cycle for d <", d, "is", longestCycle)
