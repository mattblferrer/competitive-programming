# declare variables
frequencies = []  # list of frequencies of digits of cube of index ctr
ctr = 0

# main loop
while True:
    current_freq = sorted(str(ctr**3))
    frequencies.append(current_freq)

    if frequencies.count(current_freq) == 5:  # count permutations of cube
        answer = frequencies.index(current_freq)**3
        break

    ctr += 1

# print result
print(f"The smallest cube for which exactly 5 of its permutations are cube is {answer}")
