from collections import Counter


# returns the frequencies of digits of the cube of a number num
def cube_digits(num: int) -> dict:
    cube = str(num**3)
    freq = dict(Counter(cube)) # frequencies of each digit in the cube

    return freq


# declare variables
frequencies = []  # list of frequencies of digits of cube of index ctr
ctr = 0

# main loop
while True:
    currentFreq = cube_digits(ctr)
    frequencies.append(currentFreq)

    if frequencies.count(currentFreq) == 5:  # count permutations of cube
        answer = frequencies.index(currentFreq)**3
        break

    ctr += 1

# print result
print(f"The smallest cube for which exactly 5 of its permutations are cube is {answer}")
