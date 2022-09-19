# read from file names.txt
with open('p022_names.txt', 'r') as f:
    names = f.read()

# cleaning and sorting input
names = sorted(names.replace('"', '').split(","))

# getting name scores
nameScore = 0

for i, currentName in enumerate(names, start=1):  # iterate through sorted name list
    nameScore += i*sum(ord(char) - 64 for char in currentName)  # uppercase ascii, corrected

# print result
print(f"The total of all the name scores in the file is {nameScore}")
