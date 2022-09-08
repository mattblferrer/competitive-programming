"""
These functions generate the figurate or polygonal numbers from P3 to P8
"""


# generate triangular number of certain index
def triangular(ind: int) -> int:
    return ind*(ind+1)//2


# generate square number of certain index
def square(ind: int) -> int:
    return ind*ind


# generate pentagonal number of certain index
def pentagonal(ind: int) -> int:
    return ind*(3*ind-1)//2


# generate hexagonal number of certain index
def hexagonal(ind: int) -> int:
    return ind*(2*ind-1)


# generate heptagonal number of certain index
def heptagonal(ind: int) -> int:
    return ind*(5*ind-3)//2


# generate octagonal number of certain index
def octagonal(ind: int) -> int:
    return ind*(3*ind-2)


# selects figurate number to calculate based on key
def calc_figurate(key: int, ind: int) -> int:
    figurates = {
        3: triangular,
        4: square,
        5: pentagonal, 
        6: hexagonal, 
        7: heptagonal, 
        8: octagonal
    }
    return figurates.get(key)(ind)


# find ordered set of cyclic numbers
def ord_set_cyclic(figurateNums: list) -> list:
    def backtrack() -> tuple:
        c, p = numIndex[-1] + 1, numIndex[-2]

        currentCycle.pop(-1)
        numIndex.pop(-1)
        keysUsed.pop(-1)

        return c, p

    for s, figurateNum in enumerate(figurateNums):
        currentCycle = [figurateNum]
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
                    c, p = 0, numIndex[-1]

                c += 1  # increment if check does not work

                # check if last two digits of 6th num = first two digits of 1st num (cycle)
                if len(currentCycle) == 6:
                    if currentCycle[5][1] % 100 == currentCycle[0][1] // 100:
                        return currentCycle
                    c, p = backtrack()

            if 1 < len(currentCycle) < 6:  # if no new element of cycle found, backtrack
                c, p = backtrack()
            else:
                break


# calculate list of figurate numbers between lower and upper limits
lowerLimit, upperLimit = 1000, 10000
figurateNums = []

for key in range(3, 9):
    num, index = 0, 0

    while num < upperLimit:
        num = calc_figurate(key, index)

        if lowerLimit < num < upperLimit:
            figurateNums.append((key, num))

        index += 1

# calculate sum of ordered set of cyclic numbers
cycle = ord_set_cyclic(figurateNums)  # cycle found
cyclicSum = sum(num[1] for num in cycle)

# print result
print(f"The sum of the ordered set of cyclic numbers is {cyclicSum}")
print(f"Set found: {cycle}")
