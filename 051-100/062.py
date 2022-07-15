# returns the frequencies of digits of the cube of a number num
def cube_digits(num):
    cube = str(num**3)
    freq = [0]*10  # frequencies of each digit in the cube

    for digit in cube:
        freq[int(digit)] += 1

    return freq


# declare variables
frequencies = []  # list of frequencies of digits of cube of index ctr
ctr = 0

# main loop
while True:
    currentFreq = cube_digits(ctr)
    frequencies.append(currentFreq)

    if frequencies.count(currentFreq) == 5:  # count permutations of cube
        answer = currentFreq
        break

    ctr += 1

# print result
print("The smallest cube for which exactly 5 of its permutations are cube is", frequencies.index(answer)**3)
