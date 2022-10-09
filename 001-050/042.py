# read from file words.txt
with open('p042_words.txt', 'r') as f:
    words = f.read().replace('"', '').split(",")  # cleaning input

# word score
triangleWords = 0
for word in words:
    wordScore = sum(ord(char) - 64 for char in word)  # uppercase ascii
    
    if ((wordScore*8+1)**0.5).is_integer():  # triangular number test
        triangleWords += 1

# final output
print("The number of triangle words is", triangleWords)
