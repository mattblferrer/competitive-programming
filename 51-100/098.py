import math
from collections import Counter


# read file
file1 = open('p098_words.txt', 'r')
words = file1.readline().replace('"', '').split(",")  # process line, remove quotes

# find anagrams
frequencies = []  # frequencies of letters in the word
anagrams = []  # list of anagram word pairs

for word in words:
    frequency = Counter(word)

    for i in range(len(frequencies)):
        if frequencies[i] == frequency:
            anagrams.append((word, words[i]))  # append current word and past word

    frequencies.append(frequency)

# main loop
squares = {}
num_anagrams = {}  # dict of anagram squares
maximumSquare = 0

for pair in anagrams:
    # calculate squares
    wordLength = len(pair[0])

    if wordLength not in squares.keys():  # check if squares with number of digits already calculated
        squares[wordLength] = []
        lowerLimit = int(math.sqrt(10**(wordLength-1)))
        upperLimit = int(math.sqrt(10**wordLength))

        for i in range(upperLimit, lowerLimit, -1):  # add squares sorted from highest to lowest
            squares[wordLength].append(i**2)

    # calculate square anagram pairs
    num_frequencies = []  # frequencies of digits in the squares
    frequency = tuple(sorted([int(i) for i in Counter(pair[0]).values()]))

    if frequency not in num_anagrams.keys():  # each distribution of digits has its own key in dict
        num_anagrams[frequency] = []

        # find anagrams
        for square in squares[wordLength]:
            num_frequency = Counter(str(square))
            num_freq_array = tuple(sorted([int(i) for i in num_frequency.values()]))

            for i in range(len(num_frequencies)):
                if num_frequencies[i][1] == num_frequency:
                    num_anagrams[frequency].append((square, num_frequencies[i][0]))

            if num_freq_array == frequency:  # if frequency of num and word match
                num_frequencies.append((square, num_frequency))

    # get largest square number formed with anagrams
    for squarePair in num_anagrams[frequency]:
        for i in range(2):  # check for order (0: min first, 1: max first)
            if i == 1:
                squarePair = tuple(reversed(squarePair))

            isAnagram = True
            letterAssignment = {}  # assign letters to digits

            # 1st in pair
            for j in range(len(str(squarePair[0]))):
                letter = pair[0][j]
                digit = str(squarePair[0])[j]

                if letter not in letterAssignment.keys(): 
                    letterAssignment[letter] = digit
                elif digit != letterAssignment[letter]:
                    isAnagram = False

            # 2nd in pair
            for j in range(len(str(squarePair[1]))):
                letter = pair[1][j]
                digit = str(squarePair[1])[j]

                if digit != letterAssignment[letter]:
                    isAnagram = False

            # check for maximum
            if isAnagram and squarePair[1] > maximumSquare:
                maximumSquare = max(squarePair)
                maximumPair = pair

                break

# print result
print(maximumSquare)
print(maximumPair)
