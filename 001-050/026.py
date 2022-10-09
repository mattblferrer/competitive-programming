"""
PLAN:
Implement long division manually in Python, use that function to get lengths of 
recurring cycles
"""


# get length of recurring cycle of decimal fraction
def recurring_cycle(n: int) -> int:
    qr_list = []  # declare quotient, remainder list
    dividend = 10  # starting dividend

    # continued long division
    for i in range(n + n // 10):  # only have to check up to n + # of decimal 0s
        if dividend // n == 0:  # multiply dividend by 10 and move to the right
            dividend *= 10
            qr_list.append((0, dividend % n))

        else:
            # long division step
            quotient, remainder = divmod(dividend, n)
            dividend = remainder * 10

            # check for recurring cycle
            if remainder == 0:  # if expansion terminates
                return 0

            qr_list.append((quotient, remainder))
            for j in range(len(qr_list)-1):
                if qr_list[j][0] == quotient and qr_list[j][1] == remainder:
                    return i-j


# given parameters
d = 1000

# iterate from d downwards
for i in range(d, 0, -1):
    currentCycle = recurring_cycle(i)
    if currentCycle == i-1:
        break

# final output
print(f"The number with the longest recurring cycle for d < {d} is {i}")
