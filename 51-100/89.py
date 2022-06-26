roman_letters = ["I", "V", "X", "L", "C", "D", "M"]
letter_equivalent = [1, 5, 10, 50, 100, 500, 1000]


# returns the number equivalent of a roman letter
def num_to_roman_letter(num):
    index = letter_equivalent.index(num)
    return roman_letters[index]


# returns the number equivalent of each letter in a roman numeral string
def roman_to_num_arr(roman_num):
    number_array = []

    # iterate through every letter
    for letter in roman_num:
        # match letter to its number equivalent
        index = roman_letters.index(letter)
        number_array.append(letter_equivalent[index])

    return number_array


# from array of numbers, return the roman numeral equivalent
def num_arr_to_number(num_arr):
    # final output
    number = 0

    # analyze difference between two consecutive numbers
    for i in range(len(num_arr)-1):
        current_num = num_arr[i]
        next_num = num_arr[i+1]

        # subtractive
        if current_num < next_num:
            number -= current_num
        # additive
        else:
            number += current_num

    # add last digit in roman numeral
    number += num_arr[-1]

    return number


# returns most efficient roman numeral for a given number
def num_to_roman(num):
    roman = ""  # final output

    # iterate through list of letters decreasing
    for i in range(6, -1, -1):
        # TODO


# read file
file1 = open('p089_roman.txt', 'r')
lines = file1.readlines()

# declare variables
oldLength = 0
newLength = 0

# interpret file
for line in lines:
    oldLength += len(line)

# print result
arr = roman_to_num_arr("XCIX")
print(num_arr_to_number(arr))
