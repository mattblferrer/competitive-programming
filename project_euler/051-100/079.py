from itertools import permutations


# returns True if code is valid, False otherwise
def check_code(code: str) -> bool:
    for attempt in loginAttempts:
        # indices of digits of attempt in passcode
        dIndex = [code.index(digit) for digit in attempt]  
        if not dIndex[0] < dIndex[1] < dIndex[2]:
            return False
        
    return True


# read file
with open('p079_keylog.txt', 'r') as f:
    lines = f.readlines()

loginAttempts = set()  # remove duplicates
digits = [set() for _ in range(3)]  # get 1st, 2nd, 3rd digits

for attempt in lines:
    attempt = attempt.strip()
    loginAttempts.add(attempt)

    for i, digit in enumerate(attempt):
        digits[i].add(digit)

# print digits used
for i in range(3):
    print(f"Digit {i}: {digits[i]}")

# - 4 and 5 do not appear in the passcode at all
# - 7 only appears in digit_1, and 0 only appears in digit_3, so the passcode 
# must be of the form 7*****0
# - no digit appears in a 3-digit sequence twice, so we can assume that the
# middle digits of the passcode contains 1, 2, 3, 6, 8, 9

# generate all possible codes 
unused = "123689"
possibleCodes = ('7'+''.join(digit)+'0' for digit in permutations(unused))

# iterate through all codes and check for passcode validity
for code in possibleCodes:
    if check_code(code):  # check for validity
        print(f"code: {code}")  # print result
        break
