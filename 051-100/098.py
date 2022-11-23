from math import sqrt
from collections import Counter


def main():
    # read file
    with open('p098_words.txt', 'r') as f:
        words = f.readline().replace('"', '').split(",")

    # find anagrams
    frequencies = []  # frequencies of letters in the word
    anagrams = []  # list of anagram word pairs

    for word in words:
        frequency = Counter(word)

        for i, word_freq in enumerate(frequencies):
            if word_freq == frequency:
                # append current word and past word
                anagrams.append((word, words[i]))  

        frequencies.append(frequency)

    # main loop
    squares = {}
    num_anagrams = {}  # dict of anagram squares
    maximum_square = 0

    for pair in anagrams:
        # calculate squares
        word_length = len(pair[0])

        # check if squares with number of digits already calculated
        if word_length not in squares.keys():  
            lower_limit = int(sqrt(10**(word_length-1)))
            upper_limit = int(sqrt(10**word_length))

            # add squares sorted from highest to lowest
            squares[word_length] = (i*i for i in 
            range(upper_limit, lower_limit, -1))

        # calculate square anagram pairs
        num_frequencies = []  # frequencies of digits in the squares
        frequency = tuple(sorted([int(i) for i in Counter(pair[0]).values()]))

        # each distribution of digits has its own key in dict
        if frequency not in num_anagrams.keys():  
            num_anagrams[frequency] = []

            # find anagrams
            for square in squares[word_length]:
                num_frequency = Counter(str(square))
                num_freq_array = tuple(sorted([int(i) for i in 
                num_frequency.values()]))

                for i, frequency_2 in enumerate(num_frequencies):
                    if frequency_2[1] == num_frequency:
                        num_anagrams[frequency].append((square, frequency_2[0]))

                # if frequency of num and word match
                if num_freq_array == frequency:  
                    num_frequencies.append((square, num_frequency))

        # get largest square number formed with anagrams
        for square_pair in num_anagrams[frequency]:
            for i in range(2):  # check for order (0: min first, 1: max first)
                if i == 1:
                    square_pair = tuple(reversed(square_pair))

                is_anagram = True
                letter_assignment = {}  # assign letters to digits

                # 1st in pair
                for j, digit in enumerate(str(square_pair[0])):
                    letter = pair[0][j]

                    if letter not in letter_assignment.keys(): 
                        letter_assignment[letter] = digit
                    elif digit != letter_assignment[letter]:
                        is_anagram = False

                # 2nd in pair
                for j, digit in enumerate(str(square_pair[1])):
                    letter = pair[1][j]

                    if digit != letter_assignment[letter]:
                        is_anagram = False

                # check for maximum
                if is_anagram and square_pair[1] > maximum_square:
                    maximum_square = max(square_pair)
                    maximum_pair = pair
                    break

    # print result
    print(f"Maximum square: {maximum_square}")
    print(f"Maximum pair: {maximum_pair}")


if __name__ == "__main__":
    main()
