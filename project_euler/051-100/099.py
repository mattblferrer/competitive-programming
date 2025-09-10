"""
PLAN:
use logarithms on both sides to simplify calculations
"""
from math import log


# read from base_exp.txt
with open('p099_base_exp.txt', 'r') as f:
    lines = f.readlines()

# initializing base, power, other variables
base_power_pairs = [map(int, line.split(",")) for line in lines]
greatestValue, greatestLine = 0, 0  # greatest value

# iterating through list base_exp.txt
for line, (base, power) in enumerate(base_power_pairs):
    currentValue = power * log(base)  # using logarithm rule log(a^b) = b*log(a)
    if currentValue > greatestValue:
        greatestValue, greatestLine = currentValue, line

# final output
print(greatestLine + 1)  # +1 because of zero-indexing
