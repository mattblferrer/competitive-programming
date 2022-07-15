# read file
file1 = open('p079_keylog.txt', 'r')
lines = file1.readlines()

# remove duplicates
loginAttempts = set()

for attempt in lines:
    loginAttempts.add(attempt.strip())

# main algorithm
passcode = ""

# TODO main algorithm

