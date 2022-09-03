"""
PLAN:
use logarithms on both sides to simplify calculations
"""
from math import log10


# read from base_exp.txt
file1 = open('p099_base_exp.txt', 'r')
lines = file1.readlines()

# initializing base, power, other variables
bases = []
powers = []
greatestValue = 0  # greatest value
greatestLine = 0  # line with the greatest value

# processing input
for line in lines:
    line = line.split(",")
    bases.append(int(line[0]))
    powers.append(int(line[1]))

# iterating through list base_exp.txt
for i, (base, power) in enumerate(zip(bases, powers)):
    currentValue = power * log10(base)  # using logarithm rule log(a^b) = b*log(a)
    if currentValue > greatestValue:
        greatestValue = currentValue
        greatestLine = i

# final output
print(greatestLine + 1)  # +1 because of zero-indexing
