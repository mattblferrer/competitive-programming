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
    num = 0

    # analyze difference between two consecutive numbers
    for i in range(len(num_arr)-1):
        current_num = num_arr[i]
        next_num = num_arr[i+1]

        # subtractive
        if current_num < next_num:
            num -= current_num
        # additive
        else:
            num += current_num

    # add last digit in roman numeral
    num += num_arr[-1]

    return num


# returns most efficient roman numeral for a given number
def num_to_roman(num):
    roman = ""  # final output

    # add M's
    thousands = num // 1000
    roman += "M"*thousands
    num %= 1000

    # iterate through list of letters decreasing (starting from D)
    for i in range(5, -1, -1):
        if i % 2 == 1:  # D, L, V
            if num // letter_equivalent[i] == 1:
                roman += roman_letters[i]
                num %= letter_equivalent[i]

        else:  # C, X, I
            run_length = num // letter_equivalent[i]

            if run_length < 4:  # additive
                roman += roman_letters[i]*run_length

            else:  # subtractive
                roman += roman_letters[i] + roman_letters[i+1]

            num %= letter_equivalent[i]

    # replace sequences of letters with more efficient version
    roman = roman.replace("DCD", "CM").replace("LXL", "XC").replace("VIV", "IX")

    return roman


# read file
file1 = open('p089_roman.txt', 'r')
lines = file1.readlines()

# declare variables
oldLength = 0
newLength = 0

# interpret file
for line in lines:
    line = line.rstrip()

    oldLength += len(line)

    # convert to efficient roman num
    arr = roman_to_num_arr(line)
    number = num_arr_to_number(arr)
    romanConverted = num_to_roman(number)
    newLength += len(romanConverted)

# print result
print("Number of characters saved:", oldLength - newLength)
