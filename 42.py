# read from file words.txt
file1 = open('p042_words.txt', 'r')
words = file1.read()

# cleaning input
words = words.replace('"', '').split(",")

# word score
triangleWords = 0
for word in words:
    wordScore = 0
    for char in word:
        wordScore += ord(char) - 64  # uppercase ascii
    if ((wordScore*8+1)**0.5).is_integer():  # triangular number test
        triangleWords += 1

# final output
print("The number of triangle words is", triangleWords)
