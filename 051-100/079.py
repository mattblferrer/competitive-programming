from itertools import permutations


# read file
file1 = open('p079_keylog.txt', 'r')
lines = file1.readlines()

# remove duplicates
loginAttempts = set()

# get 1st, 2nd, 3rd digits
digits = [set() for _ in range(3)]

for attempt in lines:
    attempt = attempt.strip()
    loginAttempts.add(attempt)

    for i in range(3):
        digits[i].add(attempt[i])

# main algorithm
passcode = ""

# print digits used
for i in range(3):
    print(f"Digit {i}:", digits[i])

# - 4 and 5 do not appear in the passcode at all
# - 7 only appears in digit_1, and 0 only appears in digit_3, so the passcode 
# must be of the form 7*****0
# - no digit appears in a 3-digit sequence twice, so we can assume that the
# middle digits of the passcode contains 1, 2, 3, 6, 8, 9

# generate all possible codes 
unused = "123689"
possibleCodes = ['7'+''.join(digit)+'0' for digit in list(permutations(unused))]

# iterate through all codes and check for passcode validity
for code in possibleCodes:
    isValid = True
    for attempt in loginAttempts:
        # indices of digits of attempt in passcode
        dIndex = [code.index(digit) for digit in attempt]  
        if not dIndex[0] < dIndex[1] < dIndex[2]:
            isValid = False

    # check for validity
    if isValid:
        # print result
        print("code:", code)
        break
