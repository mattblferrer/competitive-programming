# insertion sort
def insertion_sort(inputlist):
    for i in range(1, len(inputlist)):
        nextelement = inputlist[i]
        j = i-1
        while inputlist[j] > nextelement and j >= 0:
            inputlist[j+1] = inputlist[j]
            j -= 1
        inputlist[j+1] = nextelement
    return inputlist


# read from file names.txt
file1 = open('p022_names.txt', 'r')
names = file1.read()

# cleaning and sorting input
names = names.replace('"', '').split(",")
names = insertion_sort(names)

# getting name scores
nameScore = 0
for i in range(1, len(names)+1):  # iterate through sorted name list
    currentName = names[i-1]
    for char in currentName:
        charScore = ord(char) - 64  # uppercase ascii, corrected
        nameScore += i*charScore

print("The total of all the name scores in the file is", nameScore)

file1.close()
