"""
for numbers:
1-19: count as usual
20-99: split into 10*a + b
100-999: split into 100*a + 10*b + c, add 3 if b+c > 0 (for "and")
1000: add manually
"""

letterNumber = 0  # total number of letters (output)
# arrays of lengths of words
oneToNineteen = [3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8]  # 1 to 19
multiplesOfTen = [6, 6, 5, 5, 5, 7, 6, 6]  # 20 to 90

# loop through tens and ones digits
for hundreds in range(10):  # hundreds digit 0 to 9
    if hundreds > 0:
        # not counting "and" for multiples of 100
        letterNumber += 100*(oneToNineteen[hundreds - 1] + 10) - 3  # 10 letters from "hundred and"

    # 1 to 19
    for i in range(19):
        letterNumber += oneToNineteen[i]

    # 20 to 99
    for i in range(8): # 2 to 9
        letterNumber += multiplesOfTen[i]  # for numbers ending in 0
        for j in range(9):
            letterNumber += (multiplesOfTen[i] + oneToNineteen[j])

# 1000
letterNumber += 11  # one thousand

print("Number of letters needed: " + str(letterNumber))