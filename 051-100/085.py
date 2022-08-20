# generate triangular number of certain index
def triangular(ind):
    return ind*(ind+1)//2


# returns the number of smaller rectangles in a rectangle of a certain length and width
def count_rectangles(length, width):
    return triangularNums[width]*triangularNums[length]


# declare variables
limit = 2000000
loopLimit = 100  # increased loop limit manually
triangularNums = []
lowestDifference = limit
lowestDimensions = [0, 0]

# generate list of triangular numbers
for i in range(loopLimit):
    triangularNums.append(triangular(i))

# main loop (iterate through a x b rectangles)
for a in range(1, loopLimit):  
    for b in range(1, a+1):
        rectangleNumber = count_rectangles(a, b)
        difference = abs(limit - rectangleNumber)

        if difference < lowestDifference:
            lowestDifference = difference
            lowestDimensions[0], lowestDimensions[1] = a, b

# print result
print("Dimensions:", lowestDimensions)
print("Area:", lowestDimensions[0]*lowestDimensions[1])
print("Rectangles:", count_rectangles(lowestDimensions[0], lowestDimensions[1]))


