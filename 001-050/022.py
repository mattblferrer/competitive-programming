# read from file names.txt
file1 = open('p022_names.txt', 'r')
names = file1.read()

# cleaning and sorting input
names = sorted(names.replace('"', '').split(","))

# getting name scores
nameScore = 0

for i, currentName in enumerate(names, start=1):  # iterate through sorted name list
    nameScore += i*sum(ord(char) - 64 for char in currentName)  # uppercase ascii, corrected

# print result
print("The total of all the name scores in the file is", nameScore)
file1.close()  # close file
