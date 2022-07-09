"""
These functions generate the figurate or polygonal numbers from P3 to P8
"""


# generate triangular number of certain index
def triangular(ind):
    return ind*(ind+1)//2


# generate square number of certain index
def square(ind):
    return ind*ind


# generate pentagonal number of certain index
def pentagonal(ind):
    return ind*(3*ind-1)//2


# generate hexagonal number of certain index
def hexagonal(ind):
    return ind*(2*ind-1)


# generate heptagonal number of certain index
def heptagonal(ind):
    return ind*(5*ind-3)//2


# generate octagonal number of certain index
def octagonal(ind):
    return ind*(3*ind-2)


# selects figurate number to calculate based on key
def calc_figurate(key, ind):
    if key == 3:
        return triangular(ind)
    elif key == 4:
        return square(ind)
    elif key == 5:
        return pentagonal(ind)
    elif key == 6:
        return hexagonal(ind)
    elif key == 7:
        return heptagonal(ind)
    elif key == 8:
        return octagonal(ind)
    return 0


# calculate list of figurate numbers between lower and upper limits
lowerLimit, upperLimit = 1000, 10000

figurateNums = []
key = 3

while key < 9:
    num, index = 0, 0

    while num < upperLimit:
        num = calc_figurate(key, index)

        if lowerLimit < num < upperLimit:
            figurateNums.append((key, num))

        index += 1

    key += 1

# generate all possible cycles
possibleCycles = []
s = 0

while len(possibleCycles) == 0:  # iterate through all starting nums until ans is found
    currentCycle = [figurateNums[s]]
    keysUsed = [figurateNums[s][0]]

    numIndex = [s]  # indices of processed numbers
    c, p = s, s  # current, previous index

    while len(currentCycle) < 6:
        while c < len(figurateNums):
            # check for first and last two digits and if keys are different
            if figurateNums[c][1] // 100 == figurateNums[p][1] % 100 and figurateNums[c][0] not in keysUsed:
                currentCycle.append(figurateNums[c])
                numIndex.append(c)
                keysUsed.append(figurateNums[c][0])

                # move forward in cycle
                p = numIndex[-1]
                c = 0

            c += 1  # increment if check does not work

            # check if last two digits of 6th num = first two digits of 1st num (cycle)
            if len(currentCycle) == 6:
                if currentCycle[5][1] % 100 == currentCycle[0][1] // 100:
                    possibleCycles.append(currentCycle)
                    break

                c = numIndex[-1] + 1
                p = numIndex[-2]

                currentCycle.pop(-1)
                numIndex.pop(-1)
                keysUsed.pop(-1)

        if 1 < len(currentCycle) < 6:  # if no new element of cycle found, backtrack
            c = numIndex[-1] + 1
            p = numIndex[-2]

            currentCycle.pop(-1)
            numIndex.pop(-1)
            keysUsed.pop(-1)

        else:
            s += 1
            break

# calculate sum
cyclicSum = 0

for num in possibleCycles[0]:
    cyclicSum += num[1]

# print result
print("The sum of the ordered set of cyclic numbers is", cyclicSum)
print("Sets found:", possibleCycles)
