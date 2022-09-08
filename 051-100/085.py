# generate triangular number of certain index
def triangular(ind: int) -> int:
    return ind*(ind+1)//2


# returns the number of smaller rectangles in a rectangle of a certain length and width
def count_rectangles(length: int, width: int) -> int:
    return triangularNums[width]*triangularNums[length]


# declare variables
limit = 2000000
loopLimit = 100  # increased loop limit manually
lowestDifference = limit
lowestDimensions = [0, 0]

# generate list of triangular numbers
triangularNums = [triangular(i) for i in range(loopLimit)]

# main loop (iterate through a x b rectangles)
for a in range(1, loopLimit):  
    for b in range(1, a+1):
        rectangleNumber = count_rectangles(a, b)
        difference = abs(limit - rectangleNumber)

        if difference < lowestDifference:
            lowestDifference = difference
            lowestDimensions[0], lowestDimensions[1] = a, b

# print result
print(f"Dimensions: {lowestDimensions}")
print(f"Area: {lowestDimensions[0]*lowestDimensions[1]}")
print(f"Rectangles: {count_rectangles(lowestDimensions[0], lowestDimensions[1])}")
